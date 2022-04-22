#include <string>
#include "PhoneNumber.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {

    PhoneNumber phone;
    cout << "Insira valor para o telefone na forma (123) 456-789" << endl;
    // sobreescrita de operador >>
    cin >> phone;

    cout << "O telefone é: " << endl;
    //sobreescrita de operador <<
    cout << phone;
}