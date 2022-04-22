#include "Tigre.h"
#include <iostream>



using namespace std;

namespace poo { 
    Tigre::Tigre(float peso) : Animal(peso) {
        
    }   

    float Tigre::getPeso() const {
        return Animal::getPeso() * 3;
    }

    void Tigre::imprimir() const {
        cout << "O peso do tigre é: " << Tigre::getPeso() << "kg" << endl;
    }
}