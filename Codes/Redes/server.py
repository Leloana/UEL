import socket

def server_program():
    host = '0.0.0.0'  # Endereço IP do servidor (0.0.0.0 permite que o servidor aceite conexões de qualquer endereço IP)
    port = 5001  # Número da porta para ouvir

    server_socket = socket.socket()  # Instancia um novo socket
    server_socket.bind((host, port))  # Liga o socket ao endereço IP e porta especificados

    server_socket.listen(1)  # Habilita o servidor para aceitar conexões; 1 é o número máximo de conexões pendentes

    print("Servidor aguardando conexões...")

    conn, address = server_socket.accept()  # Aceita uma nova conexão
    print(f"Conexão de: {address}")

    while True:
        data = conn.recv(1024).decode()  # Recebe dados do cliente
        if not data:
            # Se não houver dados, desconecta
            break
        print(f"Mensagem recebida do cliente: {data}")

        data = input(' -> ')  # Solicita a resposta do usuário (servidor)
        conn.send(data.encode())  # Envia a resposta ao cliente

    conn.close()  # Fecha a conexão

if __name__ == '__main__':
    server_program()
