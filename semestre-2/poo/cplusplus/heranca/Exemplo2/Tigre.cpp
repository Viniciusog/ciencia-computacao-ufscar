#include "Tigre.h"

namespace poo { 
    Tigre::Tigre(float peso) : Animal(peso) {
        
    }   

    float Tigre::getPeso() const {
        return Animal::getPeso() * 3;
    }

    void Tigre::imprimir() const {
        cout << "O peso do tigre é: " << this->getPeso() << "kg" << endl;
    }
}