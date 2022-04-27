#include "Pontos2D.cpp"
#include <iostream>
using std::endl;
using std::cout;
using std::cin;

int main() {
    Ponto2D p1(3, 4);
    Ponto2D p2(5, 6);

    cout << "A distância entre os dois pontos é: " << p1.distancia(p2) << endl;
}