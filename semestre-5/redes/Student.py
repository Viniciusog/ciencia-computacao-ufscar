class Student:
    def __init__(self, name, age, grade):
        self.name = name
        self.age = age
        self.grade = grade   # 0 - 100

    def get_grade(self):
        return self.grade
    
    def print_student(self):
        print("Name: " + self.name + ", age: " + str(self.age) + ", grade: " + str(self.grade))

class Course:
    def __init__(self, name, max_students):
        self.name = name
        self.max_students = max_students
        self.students = []

    def add_student(self, student):
        if (len(self.students) < self.max_students):            
            self.students.append(student)
            return True
        return False

    def get_average_grade(self):
        sum = 0
        for student in self.students:
            sum += student.get_grade()
        return sum / len(self.students)

    def print_students(self):
        print("\nImprimindo...")
        for student in self.students:
            student.print_student()
    
vinicius = Student("vinicius", 20, 91)
fernanda = Student("fernanda", 21, 45)
gustavo = Student("gustavo", 21, 91)
programacao = Course("programação", 2)

print(programacao.add_student(vinicius))
print(programacao.add_student(fernanda))
print(programacao.add_student(gustavo))
programacao.print_students()

print(programacao.get_average_grade())

