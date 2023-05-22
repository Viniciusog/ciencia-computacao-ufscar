class Pet:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def printPet(self):
        print("Name: " + self.name + ", age: " + str(self.age))
    
    def show(self):
        print("Show Pet")

class Dog(Pet):
    def __init__(self, attDog):
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
        print("Show cat")

myPet = Pet("toto", 6)
myPet.printPet()
myPet.show()

# Aqui estou passando chave valor e dentro do construtor (__init__) iremos conseguir pegar esse valor lá dentro
myCat = Cat("lili", 2, 37, 38, 39, attCat = 8)
print("\n --cat--\n" + str(myCat.attCat))
print(myCat.anotherAttributes) # (37, )

class Fish():
    pass
