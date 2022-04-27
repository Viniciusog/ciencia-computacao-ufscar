#include <string>
#include <iostream>
using std::string;
using std::endl;
using std::cout;

#include "./Funcionario.h"


int main() {

    Pessoa *p = new Pessoa("Fernanda", 26);
    Pessoa *p2 = new Pessoa("Maria", 27);
    Pessoa *p3 = new Pessoa("Carlos", 28);

    cout << p->getNome() << endl;
    cout << p->getIdade() << endl;

    Funcionario *f = new Funcionario("Alberto", 31, 354);

    cout << f->getNome() << endl;
    cout << f->getNumeroCarteira() << endl;

}