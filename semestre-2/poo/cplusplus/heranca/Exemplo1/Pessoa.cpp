#include "Pessoa.h"
#include <string>
using std::string;

Pessoa::Pessoa(string n, int i) {
    this->nome = n;
    this->idade = i;
}

Pessoa::~Pessoa() {
    
}

void Pessoa::setNome(string nome) {
    this->nome = nome;
}

void Pessoa::setIdade(int idade) {
    this->idade = idade;
}

int Pessoa::getIdade() const {
    return idade;
}

string Pessoa::getNome() const {
    return nome;
}