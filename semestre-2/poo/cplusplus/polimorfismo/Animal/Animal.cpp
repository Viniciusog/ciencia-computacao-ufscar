using namespace std;

#include <iostream>
#include <cstdlib>
#include "Animal.hpp"

Animal::Animal(string nome) {
    this->nome = nome;
}

void Animal::setNome(string nome) {
    this->nome = nome;
}

void Animal::fazerBarulho() const {
    cout << "Barulho de animal" << endl;
}

void Animal::comer() const {
    cout << "Animal comendo..." << endl;
}