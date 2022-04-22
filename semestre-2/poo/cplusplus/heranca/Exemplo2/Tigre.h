#ifndef TIGRE_H
#define TIGRE_H

#include "Animal.h"
using namespace std;

namespace poo {
    class Tigre : public Animal {
        public:
            Tigre(float peso);
            float getPeso() const;
            void imprimir() const;
    };   
}

#endif

