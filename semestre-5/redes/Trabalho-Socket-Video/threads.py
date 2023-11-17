import threading

def thread_a():
    def funcaoImprimir():
        print("Imprimindo")
    
    while True:
        funcaoImprimir()

minha_thread_a = threading.Thread(target=thread_a, args=())
minha_thread_a.start()
