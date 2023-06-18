from _thread import *
import os
import socket

ServerSideSocket = socket.socket()
HOST = "127.0.0.1"
PORT = 65432
ThreadCount = 0

try:
    ServerSideSocket.bind((HOST, PORT))
except socket.error as e:
    print(str(e))

print("Server is listening...")
ServerSideSocket.listen() #Fica escutando possíveis conexões