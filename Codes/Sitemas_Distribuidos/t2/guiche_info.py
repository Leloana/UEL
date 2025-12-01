import grpc
from concurrent import futures
from datetime import datetime
import random

import guiche_info_pb2
import guiche_info_pb2_grpc

# Lista de terminais disponíveis (endereços e portas)
TERMINAIS = [
    'localhost:50151',  # terminal1
    'localhost:50152',  # terminal2
    'localhost:50153',  # terminal3
]

class InformationServicer(guiche_info_pb2_grpc.InformationServicer):
    def GetTerminalOnLine(self, request, context):
        # Seleciona um terminal aleatoriamente
        terminal_escolhido = random.choice(TERMINAIS)
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print(f"[{timestamp}] Terminal selecionado: {terminal_escolhido}")
        
        # Registra no log (opcional)
        with open("guiche_info_log.txt", "a", encoding="utf-8") as log:
            log.write(f"[{timestamp}] Terminal escolhido: {terminal_escolhido}\n")

        # Retorne um InfoReply (não TerminalAddress)
        return guiche_info_pb2.InfoReply(message=terminal_escolhido)


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    guiche_info_pb2_grpc.add_InformationServicer_to_server(InformationServicer(), server)
    server.add_insecure_port('[::]:50051')  # Porta padrão para o guichê
    print("Guichê de Informações ativo em localhost:50051")
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    serve()
