import grpc
import guiche_info_pb2
import guiche_info_pb2_grpc

from limpar_logs import limpar_logs_clientes, limpar_logs_terminais

import terminal_pb2
import terminal_pb2_grpc

import threading
from multiprocessing.pool import ThreadPool
import time
from concurrent import futures

import random
from datetime import datetime

# Não precisamos mais do guichê para “desvendar” o terminal.
# Manteremos o INFO_ADDRESS para fins de log, mas não o usaremos de fato.
INFO_ADDRESS = 'localhost:50051'

nomes = ["Alice", "Bob", "Charlie", "David", "Eve", "Nick", "Ema", "Maria"]

# Lista fixa de todos os terminais que existem
lista_terminais = [
    "localhost:50151",  # Terminal 1
    "localhost:50152",  # Terminal 2
    "localhost:50153"   # Terminal 3
]

# Variável global para log de callback
ID_CLIENTE_GLOBAL = None


# -------------------------------------------------------------------
# CallbackService: faz do cliente um pequeno servidor gRPC
# -------------------------------------------------------------------
class CallbackServiceServicer(terminal_pb2_grpc.CallbackServiceServicer):
    def ReceiveCallback(self, request, context):
        nome = request.nomeVeiculo
        status = request.status
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print(f"\n[Callback] Cliente recebeu: {status} - {nome} [{timestamp}]")
        log_cliente(ID_CLIENTE_GLOBAL, f"Recebeu callback: {status} - {nome}")
        return terminal_pb2.CallbackResponse(status="OK")


def start_client_as_server(port):
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=1))
    terminal_pb2_grpc.add_CallbackServiceServicer_to_server(CallbackServiceServicer(), server)
    server.add_insecure_port(f"[::]:{port}")
    print(f"Cliente (Servidor Callback) iniciado na porta {port}...")
    server.start()
    try:
        server.wait_for_termination()
    except Exception as e:
        print(f"Cliente (Servidor Callback) interrompido: {e}")


def log_cliente(nome, mensagem):
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open(f"clientes_log/cliente_{nome}.txt", "a", encoding="utf-8") as f:
        f.write(f"{mensagem} em [{timestamp}]\n")


def tentar_rent_no_terminal(terminal, nome_cliente, classe, IP, Porta):
    """
    Chama RentACar em um terminal específico.
    Retorna (status, veiculo) ou lança RpcError se terminal indisponível.
    """
    with grpc.insecure_channel(terminal) as canal:
        stub = terminal_pb2_grpc.TerminalStub(canal)
        req = terminal_pb2.RentCarRequest(
            ID_cliente=nome_cliente,
            IP_cliente=IP,
            Porta_cliente=Porta,
            Classe_veiculo=classe
        )
        resp = stub.RentACar(req)  # Pode retornar status=NAO_SUPORTADO, PENDENTE ou CONCLUIDO
        return resp.status, resp.message  # message vai conter nome do veículo ou ""


def tentar_return_no_terminal(terminal, nome_cliente, classe, veiculo):
    """
    Chama ReturnACar em um terminal específico.
    Retorna status True/False ou lança RpcError se terminal indisponível.
    """
    with grpc.insecure_channel(terminal) as canal:
        stub = terminal_pb2_grpc.TerminalStub(canal)
        req = terminal_pb2.ReturnCarRequest(
            ID_cliente=nome_cliente,
            Nome_veiculo=veiculo,
            Classe_veiculo=classe
        )
        resp = stub.ReturnACar(req)
        # resp.status será "DEVOLVIDO" ou "NAO_SUPORTADO"
        return resp.status == "CONCLUIDO"  # devolução bem sucedida se status==CONCLUIDO


def cliente(classe: str, ind: int, i: int):
    global ID_CLIENTE_GLOBAL

    classe = classe.strip()
    IP = 'localhost'
    if i < 10:
        Porta = '4000' + str(i)
    elif i < 100:
        Porta = '400' + str(i)
    else:
        Porta = '40' + str(i)

    nome_cliente = nomes[ind]
    ID_CLIENTE_GLOBAL = nome_cliente

    # 1) Inicia servidor de callback para receber notificações de fila
    server_thread = threading.Thread(
        target=start_client_as_server, args=(Porta,), daemon=True
    )
    server_thread.start()
    time.sleep(1)

    try:
        # === 2) TENTAR ALUGAR: percorre a lista de terminais até achar o que gerencia a classe ===
        log_cliente(nome_cliente, f"Tentando alugar classe {classe} em algum terminal")
        veiculo_nome = None
        alugou = False
        for terminal in lista_terminais:
            try:
                status, mensagem = tentar_rent_no_terminal(
                    terminal, nome_cliente, classe, IP, Porta
                )
            except grpc.RpcError as e:
                # Se o canal falha (terminal morto), tenta o próximo
                print(f"[AVISO] {nome_cliente}: não conseguiu conectar com {terminal} ({e.code()})")
                continue

            # Se o terminal respondeu “NAO_SUPORTADO”, não é o terminal certo: tenta outro
            if status == "NAO_SUPORTADO":
                log_cliente(nome_cliente, f"Terminal {terminal} não suporta classe {classe}→seguindo")
                continue

            # Se chegou aqui, status é “PENDENTE” ou “CONCLUIDO”, logo esse terminal gerencia a classe
            log_cliente(nome_cliente, f"Resposta de {terminal}: {status} {mensagem if status=='CONCLUIDO' else ''}")
            # Se já alugou, captura o nome do veículo
            if status == "CONCLUIDO":
                veiculo_nome = mensagem
                alugou = True
            break  # saiu do loop, pois encontrou terminal que gerencia a classe

        if not alugou:
            # Se nenhum terminal suportou a classe, finaliza (ou poderia ficar em espera)
            log_cliente(nome_cliente, f"Não existe terminal que suporte classe {classe}")
            return

        # 2.1) Se conseguiu o carro (status=CONCLUIDO), simula o uso
        if alugou:
            tempo_uso = random.randint(2, 5)
            time.sleep(tempo_uso)

            # === 3) TENTAR DEVOLVER: percorre os mesmos terminais para encontrar onde devolver ===
            log_cliente(nome_cliente, f"Tentando devolver {veiculo_nome} (classe {classe})")
            devolvido = False
            for terminal in lista_terminais:
                try:
                    sucesso = tentar_return_no_terminal(terminal, nome_cliente, classe, veiculo_nome)
                except grpc.RpcError as e:
                    print(f"[AVISO] {nome_cliente}: não conseguiu conectar com {terminal} para devolução ({e.code()})")
                    continue

                if not sucesso:
                    # Retornou NAO_SUPORTADO → não é o terminal que gerencia essa classe
                    log_cliente(nome_cliente, f"Terminal {terminal} não suporta devolução de classe {classe}")
                    continue

                # Se entrou aqui, devolveu com sucesso (CONCLUIDO)
                log_cliente(nome_cliente, f"Carro devolvido: {veiculo_nome} na classe {classe}")
                devolvido = True
                break

            if not devolvido:
                # Nenhum terminal aceitou a devolução (algo muito errado)
                log_cliente(nome_cliente, f"Não conseguiu devolver {veiculo_nome} (classe {classe}) em nenhum terminal")

    except grpc.RpcError as e:
        print(f"[ERRO] {nome_cliente}: Erro gRPC inesperado: {e.code()} - {e.details()}")


def main():
    num_threads = 5

    try:
        with open('carros_solicitados.txt', 'r') as f:
            linhas = [linha.strip() for linha in f if linha.strip()]
    except FileNotFoundError:
        print("Erro: O arquivo 'carros_solicitados.txt' não foi encontrado.")
        return
    except Exception as e:
        print(f"Erro ao ler 'carros_solicitados.txt': {e}")
        return

    if not linhas:
        print("Atenção: 'carros_solicitados.txt' está vazio ou sem classes válidas.")
        return

    print(f"\nProcessando {len(linhas)} requisições com até {num_threads} threads simultâneas.")

    with ThreadPool(processes=num_threads) as pool:
        tasks = [pool.apply_async(cliente, (linhas[i], i % 8, i)) for i in range(len(linhas))]
        for idx, result in enumerate(tasks):
            try:
                result.get()
            except Exception as exc:
                print(f"Requisição {idx} gerou exceção: {exc}")


if __name__ == '__main__':
    limpar_logs_clientes()
    limpar_logs_terminais()
    main()

'''
os clientes utilizam portas entre:
40000 a 50000
'''
