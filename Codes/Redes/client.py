import socket

def client_program():
    host = '127.0.0.1'  # endereço IP do servidor
    port = 5001  # número da porta do servidor de socket

    try:
        client_socket = socket.socket()  # instancia um novo socket
        client_socket.connect((host, port))  # conecta ao servidor

        message = input(" -> ")  # solicita a entrada do usuário

        while message.lower().strip() != 'bye':
            client_socket.send(message.encode())  # envia a mensagem
            data = client_socket.recv(1024).decode()  # recebe a resposta

            print('Received from server: ' + data)  # exibe a resposta no terminal

            message = input(" -> ")  # solicita novamente a entrada do usuário

        client_socket.close()  # fecha a conexão
    except ConnectionRefusedError:
        print(f"Erro: Não foi possível conectar-se ao servidor em {host}:{port}. Verifique se o servidor está em execução.")
    except Exception as e:
        print(f"Erro inesperado: {e}")

if __name__ == '__main__':
    client_program()
