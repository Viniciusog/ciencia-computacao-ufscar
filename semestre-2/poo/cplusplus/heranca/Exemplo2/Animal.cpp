#include "Animal.h"

using namespace std;
// #define std::endl;

namespace poo {
    Animal::Animal(float p) {
        this->peso = p;
    }

    Animal::~Animal() {

    }

    void Animal::setPeso(float peso) {
        this->peso = peso;
    }

    float Animal::getPeso() const {
        return this->getPeso();
    }

    void Animal::imprimir() const {
        cout << "O peso do animal é: " << this->peso << "kg" << endl;
    }
}