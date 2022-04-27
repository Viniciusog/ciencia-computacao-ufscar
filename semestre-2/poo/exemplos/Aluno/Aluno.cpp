#include "Aluno.h"
#include <iostream>
#include <string>
#include <iomanip>

using std::string;
using std::to_string;
using std::cout;
using std::endl;
using std::setprecision;

// inicialização de atributo estático
int Aluno::qtdAlunos = 0;
int Aluno::contadorRA = 1;

Aluno::Aluno(string n, int qtdNotas) : ra(Aluno::getContadorRA()) {
    nome = n;
    notas = new float[qtdNotas];
    this->qtdNotas = qtdNotas;

    // Inicializa o array de notas sendo -1
    for (int i = 0; i < qtdNotas; i++) {
        notas[i] = -1;
    }

    // Toda vez que um aluno for criado, incrementaremos o valor da quantidade de alunos;
    qtdAlunos++;
    // O contador de RA não representa a quantidade total de alunos, pois os alunos podem 
    // ser excluidos e o valor do RA é sempre crescente.
    contadorRA++;
}

// Destrutor
Aluno::~Aluno() {
    delete [] notas; // desalocando o espaço das notas
    qtdAlunos--;
}   

void Aluno::setNome(string n) {
    nome = n;
}

string Aluno::getNome() const {
    return nome;
}

int Aluno::getRA() const {
    return ra;
}

int Aluno::getQtdAlunos() {
    return qtdAlunos;
}

int Aluno::getContadorRA() {
    return contadorRA;
}

void Aluno::addNota(float nota, int posicao) {
    // Se podemos inserir 5 notas, o array vai de 0 até 4
    if (posicao >= 0 && posicao < qtdNotas) {
        notas[posicao] = nota;
    }
}

// Se a nota não foi inserida pelo usuário, mostra um traço '-'
void Aluno::imprimirNotas() {
    for (int i = 0; i < qtdNotas; i++) {
        if (notas[i] != -1) {
            cout << setprecision(2) << notas[i] << " ";
        } else {
            cout << "- ";
        }
    }
    cout << endl;
}