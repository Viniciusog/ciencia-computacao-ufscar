#include "Animal.cpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {

    Animal a("Elefante");

    string nomeDoAnimal;

    cout << "Entre com o tipo de animalanima" << endl;
    getline(cin, nomeDoAnimal);

    a.setNome(nomeDoAnimal);

    a.fazerBarulho();

    return 0;
}