#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

#include "Aluno.cpp"

int main() {

    Aluno *a1 = new Aluno("Fernando", 4);
    a1->getRA();

    Aluno *a2 = new Aluno("Maria", 5);
    a2->getRA();

    Aluno *a3 = new Aluno("Gabrielly", 6);
    a3->getRA();

    Aluno *a4 = new Aluno("Roberto", 7);
    a4->getRA();

    Aluno *a5 = new Aluno("João", 8);
    a5->getRA();


    cout << "RA do 1º aluno: " << a1->getRA() << endl;
    cout << "RA do 2º aluno: " << a2->getRA() << endl;
    cout << "RA do 3º aluno: " << a3->getRA() << endl;
    cout << "RA do 4º aluno: " << a4->getRA() << endl;
    cout << "RA do 5º aluno: " << a5->getRA() << endl;
    cout << "Quantidade de alunos: " << a1->getQtdAlunos() << endl;

    cout << endl;
    cout << "Removendo o aluno 3..." << endl;
    delete (a3);
    cout << "Quantidade de alunos: " << a1->getQtdAlunos() << endl;

    cout << endl;

    Aluno *a6 = new Aluno("Yasmin", 9);
    a6->getRA();

    // Adiciona o aluno que seria o 6º, caso o terceiro aluno não fosse removido.
    cout << "Adicionando o 6º aluno..." << endl;
    cout << "RA do 6º aluno: " << a6->getRA() << endl;
    cout << "Quantidade de alunos: " << a1->getQtdAlunos() << endl;

    // Inserindo notas para o 2º aluno: 
    a2->addNota(8.5, 0);
    a2->addNota(8.0, 1);
    a2->addNota(9.5, 2);
    a2->addNota(10, 3);

    cout << "Notas do 2º aluno: " << endl;
    a2->imprimirNotas();

    a4->addNota(9.6, 3);

    cout << endl;
    cout << "Notas do 4º aluno: " << endl;
    a4->imprimirNotas();

}