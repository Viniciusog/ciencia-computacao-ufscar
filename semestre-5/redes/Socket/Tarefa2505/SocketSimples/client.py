from socket import *
HOST = "127.0.0.1"
PORT = 65432

with socket(AF_INET, SOCK_STREAM) as s:
   s.connect((HOST, PORT))
   s.sendall("Hello world".encode())
   data = s.recv(1024).decode()

print(f"Received {data!r}")