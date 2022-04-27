#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>

using namespace std;

namespace poo {
    class Animal {
        public:
            Animal(float p);
            virtual float getPeso() const;
            virtual void imprimir() const;
        private:
            float peso;
    };
}

#endif

