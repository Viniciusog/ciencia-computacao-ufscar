import tkinter as tk
import threading
import time

def update_number(label):
    num = 0
    while True:
        num += 1
        label.config(text=str(num))
        time.sleep(1)

# Cria a janela principal do Tkinter
root = tk.Tk()

# Cria um rótulo para exibir o número
number_label = tk.Label(root, text="0", font=("Arial", 24))
number_label.pack(pady=10)

# Cria uma thread para atualizar o número
update_thread = threading.Thread(target=update_number, args=(number_label,))
update_thread.daemon = True  # Define a thread como daemon para que ela seja encerrada quando a janela for fechada
update_thread.start()

# Inicia o loop de eventos do Tkinter
root.mainloop()
