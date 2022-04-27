#include "Animal.h"
#include <iostream>


using namespace std;
// #define std::endl;

namespace poo {
    Animal::Animal(float p) {
        this->peso = p;
    }

    float Animal::getPeso() const {
        return this->peso;
    }

    void Animal::imprimir() const {
        cout << "O peso do animal é: " << this->peso << "kg" << endl;
    }
}