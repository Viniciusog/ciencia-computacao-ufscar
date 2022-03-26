#include "Endereco.h"
#include <string>
using namespace std;


Endereco::Endereco(string rua, string bairro) {
    this->rua = rua;
    this->bairro = bairro;
}

string Endereco::getBairro() const {
    return this->bairro;
}

string Endereco::getRua() const {
    return this->rua;
}

