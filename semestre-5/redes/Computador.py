class Computador:
    def __init__(self, marca, memoria_ram, placa_de_video):
        self.marca = marca
        self.memoria_ram = memoria_ram
        self.placa_de_video = placa_de_video

    def Ligar(self):
        print("Ligando o computador " + self.marca + ", " + self.memoria_ram)
    
    def Desligar(self):
        print("Desligando o computador " + self.marca  + ", " + self.memoria_ram)
    

computador1 = Computador("Asus", "8gb", "placa pc 1")
print(computador1.marca, computador1.memoria_ram, computador1.placa_de_video)
computador2 = Computador("Samsung", "16gb", "placa pc 2")
print(computador2.marca, computador2.memoria_ram, computador2.placa_de_video)
computador3 = Computador("Samsung", "8gb", "placa pc 3")
print(computador3.marca, computador3.memoria_ram, computador3.placa_de_video)

computador3.Ligar()
computador3.Desligar()


    
