#include <string>
#include <iostream>
#include "Endereco.h"

using namespace std;

class Aluno {
    friend ostream &operator<<(ostream &output, const Aluno &aluno);
    public:
        Aluno(string nome, Endereco &e);
        string getNome() const;
        Endereco& getEndereco() const;
    private:
        string nome;
        Endereco &endereco;
};