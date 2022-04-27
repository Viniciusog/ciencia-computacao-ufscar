#include "Stack.h"
#include <iostream>

using namespace std;

int main() {    
    Stack<int> p;
    p.empilhar(8);
    p.empilhar(12);
    p.empilhar(3);
    p.empilhar(5);
    p.empilhar(2);

    p.imprimir();
}