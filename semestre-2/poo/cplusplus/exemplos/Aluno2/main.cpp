#include "Aluno.h"
#include <iostream>
#include <string>
#include <iomanip>

using std::cout;
using std::endl;

int main() {

    Aluno *a = new Aluno(3, "Fernando");
    a->setNota(8.94, 2);
    a->setNota(9.37, 0);
    a->imprimir();

    // cout << a->getNome() << endl;

    a->setNome("Amadeu");

    cout << a->getNome() << endl;
} 