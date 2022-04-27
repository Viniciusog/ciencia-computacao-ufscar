#include <string>
#include "Aluno.h"
using namespace std;

Aluno::Aluno(string nome, Endereco &e) : nome(nome), endereco(e) {

}

string Aluno::getNome() const {
    return this->nome;
}

Endereco& Aluno::getEndereco() const {
    return this->endereco;
}

ostream &operator<<(ostream &output, const Aluno &aluno) {
    output << "Nome: " << aluno.nome << ".\nMora na rua: " << aluno.endereco.getBairro() << endl;
}