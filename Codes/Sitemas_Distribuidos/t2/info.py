from concurrent import futures
import grpc
import guiche_info_pb2
import guiche_info_pb2_grpc

'''
Guichê de Informações: responde qual terminal está disponível para a classe desejada
'''

import random

terminais_disponiveis = [
    "localhost:50151",
    "localhost:50152",
    "localhost:50153"
]

class Information(guiche_info_pb2_grpc.InformationServicer):
    def GetTerminalOnLine(self, request, context):
        classe = request.name.strip()  # ainda útil para log
        online = []

        for terminal in terminais_disponiveis:
            try:
                channel = grpc.insecure_channel(terminal)
                grpc.channel_ready_future(channel).result(timeout=0.5)
                online.append(terminal)
                channel.close()
            except grpc.FutureTimeoutError:
                continue

        if not online:
            print("[INFO] Nenhum terminal disponível")
            return guiche_info_pb2.InfoReply(message="")

        destino = random.choice(online)
        return guiche_info_pb2.InfoReply(message=destino)



def server():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=2))
    guiche_info_pb2_grpc.add_InformationServicer_to_server(Information(), server)
    server.add_insecure_port('localhost:50051')
    print("Guichê de Informações Ativado na porta 50051")
    server.start()
    server.wait_for_termination()

server()
