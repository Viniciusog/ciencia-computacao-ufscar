class Dog:    
        def __init__(self, name, age):
                self.name = name
                self.age = age

        def addYears(self, years):
                self.age += years
                return self.age
        
        def printDog(self):
                print("Name: " + self.name + ", age: " + self.age)

        def set_color(self, color):
                self.color = color

dog = Dog("Toto", 5)
newAge = dog.addYears(3)
print(newAge)
print(dog.age)

dog.set_color("brown")
print(dog.color)


