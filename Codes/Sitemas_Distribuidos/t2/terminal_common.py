# terminal_common.py
import grpc
import terminal_pb2
import terminal_pb2_grpc
import backup_pb2
import backup_pb2_grpc
from datetime import datetime
import threading

lock = threading.Lock()

# Não precisamos mais do mapa fixo aqui no common,
# mas mantemos para orientação interna (não usada pelo cliente diretamente).
mapa_classes = {
    "Executivos": "localhost:50151",
    "Minivan": "localhost:50151",
    "Intermediarios": "localhost:50152",
    "SUV": "localhost:50152",
    "Economicos": "localhost:50153"
}

def log_terminal(terminal_id, mensagem):
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open(f"terminal_log/terminal_{terminal_id}.txt", "a", encoding="utf-8") as f:
        f.write(f"{mensagem} em [{timestamp}]\n")

def build_terminal_servicer(terminal_id, estoque, fila_espera):
    class TerminalServicer(terminal_pb2_grpc.TerminalServicer):
        def RentACar(self, request, context):
            cliente = request.ID_cliente
            classe = request.Classe_veiculo
            # 1) Se não gerencia essa classe, avisa “NAO_SUPORTADO”
            if classe not in estoque:
                log_terminal(terminal_id, f"Classe {classe} NÃO SUPORTADA neste terminal")
                return terminal_pb2.RentCarResponse(message="", status="NAO_SUPORTADO")

            log_terminal(terminal_id, f"Requisição recebida do cliente {cliente} para classe {classe}")
            with lock:
                # 2) Se há veículo disponível
                if estoque[classe]:
                    veiculo = estoque[classe].pop(0)
                    log_terminal(terminal_id, f"Resposta enviada ao cliente {cliente}: CONCLUIDO {classe} {veiculo}")
                    # Enviar para backup
                    try:
                        log_terminal(terminal_id, f"Requisição enviada ao servidor de backup {cliente} para classe {classe} {veiculo} CONCLUIDA")
                        with grpc.insecure_channel("localhost:50052") as canal:
                            stub = backup_pb2_grpc.BackupStub(canal)
                            _ = stub.RegistrarTransacao(backup_pb2.BackupRequest(
                                cliente=cliente, classe=classe, veiculo=veiculo, status="CONCLUIDO"
                            ))
                            log_terminal(terminal_id, f"Backup: {cliente} {classe} {veiculo} CONCLUIDO")
                    except Exception as e:
                        print(f"[ERRO BACKUP] {e}")
                    return terminal_pb2.RentCarResponse(message=veiculo, status="CONCLUIDO")
                else:
                    # 3) Sem veículo → fica em fila de espera
                    fila_espera.setdefault(classe, []).append({
                        "id": cliente,
                        "ip": request.IP_cliente,
                        "porta": request.Porta_cliente
                    })
                    log_terminal(terminal_id, f"Resposta enviada ao cliente {cliente}: PENDENTE {classe}")
                    # Também registra no backup como PENDENTE
                    try:
                        log_terminal(terminal_id, f"Requisição enviada ao servidor de backup {cliente} para classe {classe} PENDENTE")
                        with grpc.insecure_channel("localhost:50052") as canal:
                            stub = backup_pb2_grpc.BackupStub(canal)
                            _ = stub.RegistrarTransacao(backup_pb2.BackupRequest(
                                cliente=cliente, classe=classe, veiculo="", status="PENDENTE"
                            ))
                            log_terminal(terminal_id, f"Backup: {cliente} {classe} PENDENTE")
                    except Exception as e:
                        print(f"[ERRO BACKUP] {e}")
                    return terminal_pb2.RentCarResponse(message="", status="PENDENTE")

        def ReturnACar(self, request, context):
            veiculo = request.Nome_veiculo
            classe = request.Classe_veiculo
            cliente = request.ID_cliente

            if classe not in estoque:
                log_terminal(terminal_id, f"[ERRO] Cliente {cliente} tentou devolver {veiculo}, mas classe {classe} não é gerenciada por este terminal.")
                return terminal_pb2.ReturnCarResponse(message=False, status="NAO_SUPORTADO")
            
            log_terminal(terminal_id, f"Devolução recebida: cliente {cliente} devolveu {veiculo} da classe {classe}")
            
            with lock:
                # 1. Repor veículo de volta ao estoque
                estoque.setdefault(classe, []).append(veiculo)

                # 2. Registrar devolução no backup
                try:
                    log_terminal(terminal_id, f"Requisição enviada ao servidor de backup {cliente} para classe {classe} {veiculo} DEVOLVIDO")
                    with grpc.insecure_channel("localhost:50052") as canal:
                        stub = backup_pb2_grpc.BackupStub(canal)
                        resposta = stub.RegistrarTransacao(backup_pb2.BackupRequest(
                            cliente=cliente, classe=classe, veiculo=veiculo, status="DEVOLVIDO"
                        ))
                    log_terminal(terminal_id, f"Resposta recebida do servidor de backup {cliente} {classe} {veiculo} DEVOLVIDO")
                except Exception as e:
                    print(f"[ERRO BACKUP] {e}")

                # 3. Notificar cliente em fila (se houver)
                if fila_espera.get(classe):
                    proximo = fila_espera[classe].pop(0)
                    log_terminal(terminal_id, f"Callback enviado ao cliente {proximo['id']} para veículo {veiculo}")
                    try:
                        canal_cb = grpc.insecure_channel(f"{proximo['ip']}:{proximo['porta']}")
                        stub_cb = terminal_pb2_grpc.CallbackServiceStub(canal_cb)
                        stub_cb.ReceiveCallback(terminal_pb2.CallbackMessage(
                            status="CONCLUIDO",
                            nomeVeiculo=veiculo
                        ))
                    except Exception as e:
                        print(f"[ERRO CALLBACK] {e}")

            return terminal_pb2.ReturnCarResponse(message=True, status="CONCLUIDO")

    return TerminalServicer
