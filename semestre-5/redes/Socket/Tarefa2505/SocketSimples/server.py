from socket import *
HOST = "127.0.0.1"
PORT = 65432


with socket(AF_INET, SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen() #fica escutando para que possam conectar com o servidor
    conn, addr = s.accept()
    with conn:
        print(f"Connected by {addr}, connection: {conn}")
        while True:
            data = conn.recv(1024).decode()
            if not data:            
                break
            conn.sendall((data + "*").encode())