#include <iostream>
#include "Animal.h"
using std::cout;
using std::endl;
using std::cin;

Animal::Animal(string n) {
    setNome(n);
}

void Animal::setNome(string n) {
    nome = n;
}

string Animal::getNome() {
    return nome;
}

void Animal::fazerBarulho() {
    cout << "Barulho de: " << getNome() << "!" << endl;
}