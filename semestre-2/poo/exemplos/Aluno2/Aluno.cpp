#include "./Aluno.h"
#include <iostream>
#include <string>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::setprecision;

int Aluno::contadorAlunos = 0;
int Aluno::contadorRA = 1;

Aluno::Aluno(int qtdNotas, string nome) : ra(Aluno::getContadorRA()) {
    this->qtdNotas = qtdNotas;
    this->nome = nome;

    notas = new float[qtdNotas];

    for (int i = 0; i < qtdNotas; i++) {
        notas[i] = -1;
    }

    contadorAlunos++;
    contadorRA++;
}

Aluno::~Aluno() {
    delete [] notas;
    contadorAlunos--;
}

void Aluno::setNota(float nota, int pos) {
    if (pos >=0 && pos <= qtdNotas) {
        notas[pos] = nota;
    }
}

void Aluno::setNome(string n) {
    nome = n;
}

string Aluno::getNome() {
    return nome;
}

int Aluno::getRA() {
    return ra;
}

int Aluno::getQtdNotas() {
    return qtdNotas;
}

int Aluno::getContadorRA() {
    return contadorRA;
}

int Aluno::getQtdAlunos() {
    return contadorAlunos;
}

// imprimi todas as notas do aluno
void Aluno::imprimir() {
    for (int i = 0; i < qtdNotas; i++) {
        if (notas[i] != -1) {
            cout << setprecision(2) << notas[i] << " ";
        } else {
            cout << "- ";
        }
    }
    cout << endl;
}