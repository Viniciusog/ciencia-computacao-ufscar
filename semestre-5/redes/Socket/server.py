from socket import *
HOST = "127.0.0.1"
PORT = 65432

with socket(AF_INET, SOCK_STREAM) as s:
    s.bind((HOST, PORT)) # mapeia o host e a porta que serão utilizados para escutar alguma mensagem
    s.listen()

    conn, addr = s.accept()
    with conn:
        print(conn)
        print(addr)
        while True:
            data = conn.recv(1024)
            if not data:
                break
            string = str(data.decode()) + "*"
            conn.sendall(string.encode())
