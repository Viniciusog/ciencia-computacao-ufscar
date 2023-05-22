class Pet:
    def __init__(self, name, age):
        self.name = name
        self.age = age
        print("pet constructor")

    def printPet(self):
        print("Name: " + self.name + ", age: " + str(self.age))
    
    def show(self):
        print("Show Pet")

class Dog(Pet):
    def __init__(self, name, age, attDog):
        super().__init__(name, age)
        self.attDog = attDog
    
    def show(self):
        print("Show dog")
    
class Cat(Pet):
    def __init__(self, name, age, *args, **kwargs):
        self.name = name
        self.age = age
        self.anotherAttributes = args
        self.attCat = kwargs.get('attCat', -1)
    
    def show(self):
        super().show()

myPet = Pet("toto", 6)
myPet.printPet()
myPet.show()

# Aqui estou passando chave valor e dentro do construtor (__init__) iremos conseguir pegar esse valor lá dentro
myCat = Cat("lili", 2, 37, 38, 39, attCat = 8)
print("\n --cat--\n" + str(myCat.attCat))
print(myCat.anotherAttributes) # (37, )
myCat.show()

print("\n--dog--")
myDog = Dog("haka", 2, -4)
myDog.printPet()
print(myDog.attDog)

class Fish(Pet):
    quantidade_peixe = 0 # atributo estático 
    
    def __init__(self, name, age, cor):
        super().__init__(name, age)
        self.cor = cor
        Fish.quantidade_peixe += 1

    @classmethod #método da classe
    def number_of_fishes(cls):
        return cls.quantidade_peixe
    
    @staticmethod
    def static_print():
        print("printando peixe estático")

    def print_normal(self):
        print("printando peixe normal")

print("\n")
fish = Fish("nemo", 1, "orange")
fish.printPet()
print("Quantidade de peixes: " + str(fish.quantidade_peixe))

print("\n")
fish2 = Fish("teste", 4, "red")
fish2.printPet()
print("Quantidade de peixes: " + str(fish2.quantidade_peixe))

qtd = Fish.number_of_fishes()
print("Qtd classmethod: " + str(qtd))
Fish.static_print()


class Pessoa:
    def __init__(self, nome, idade):
        self.nome = nome
        self.idade = idade
    
    def falar(self, frase):
        print("Falando: " + frase)

    @classmethod #Aqui está servindo como um método factory (para criar objetos, é possível herdar)
    def criar_pessoa_com_ano_nascimento(cls, nome, ano_nascimento):
        return cls(nome, 2023 - ano_nascimento)
    
    def imprimir(self):
        print("Nome: " + self.nome + ", idade: " + str(self.idade))
    
class Professor(Pessoa):
    pass

print("\n --pessoa--")
p = Pessoa("fernando", 20)
p.imprimir()

p2 = Pessoa.criar_pessoa_com_ano_nascimento("maria", 2001)
p2.imprimir()

p3 = Professor.criar_pessoa_com_ano_nascimento("pedro", 1990)
p3.imprimir()