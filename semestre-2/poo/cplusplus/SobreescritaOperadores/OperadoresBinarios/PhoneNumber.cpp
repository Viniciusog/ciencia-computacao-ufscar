#include "PhoneNumber.h"

#include <iomanip>
using std::setw;

// Retorna endereço de objeto ostream para possibilitar chamada em cascata 
// Consegue acessar todos os atributos e fun
ostream &operator<<(ostream &output, const PhoneNumber &number) {
    output << "(" << number.areaCode << ") " 
    << number.exchange << "-" << number.line;
    return output;
}

istream &operator>>(istream &input, PhoneNumber &number) {
    //(234) 456-789
    input.ignore(); // pula (
    input >> setw(3) >> number.areaCode;
    input.ignore(2); // pula ) e espaço
    input >> setw(3) >> number.exchange;
    input.ignore(); // pula traço (-)
    input >> setw(4) >> number.line;
    return input;
}