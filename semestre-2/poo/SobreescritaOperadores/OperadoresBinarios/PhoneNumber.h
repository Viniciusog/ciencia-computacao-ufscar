#ifndef PHONENUMBER_H
#define PHONENUMBER_H

#include <iostream>
using std::ostream;
using std::istream;
#include <string>

using std::string;


/*Se precisarmos fazer a sobreescrita de operadores com o objeto da classe na 
esquerda, então precisaremos criar uma função base

Se precisarmos criar uma sobreescrita de um operador com o objeto da classe na direita
então, precisaremos criar uma função global*/
class PhoneNumber {
    //Faz a sobreescrita do operador << com o objeto PhoneNumber na direita
    // pois é uma função global. 
    friend ostream &operator<<(ostream &, const PhoneNumber &);
    friend istream &operator>>(istream &, PhoneNumber &);

    private:
        string areaCode; //Código da área da cidade com 3 algarismos
        string exchange;    //prefixo (de bairro/região) de 3 algarismos
        string line;    //linha de 4 algarismos
};

#endif