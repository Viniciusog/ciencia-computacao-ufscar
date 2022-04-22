#include "Funcionario.h"
#include <string>
using std::string;

Funcionario::Funcionario(string nome, int idade, int numCarteira) : Pessoa(nome, idade) {
    setNumeroCarteira(numCarteira);
}

Funcionario::~Funcionario() {
    
}

int Funcionario::getNumeroCarteira() const {
    return this->numeroCarteira;
}

void Funcionario::setNumeroCarteira(int numero) {
    this->numeroCarteira = numero;
}
