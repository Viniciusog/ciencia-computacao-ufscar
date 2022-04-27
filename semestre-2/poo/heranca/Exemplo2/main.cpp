#include "Animal.h"
#include "Tigre.h"
#include <iostream>

using namespace std;
using namespace poo;

int main() {
    Animal a(35);
    a.imprimir();

    // Faz a sobreescrita da função de peso e também da escrita
    Tigre t(20);
    t.imprimir();

    cout << t.getPeso() << endl;
}