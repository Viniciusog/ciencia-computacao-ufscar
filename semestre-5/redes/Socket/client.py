from socket import *
HOST = "127.0.0.1"
PORT  = 65432 # portas sem privilégio são as maiores do que 1023

# s = socket(AF_INET, SOCK_STREAM) # ipv4, tcp
with socket(AF_INET, SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.send(b"Hello world")
    data = s.recv(1024)
    print(data.decode())
