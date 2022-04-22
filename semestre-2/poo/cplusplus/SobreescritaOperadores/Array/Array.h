#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

using std::ostream;
using std::istream;

class Array {
    friend ostream &operator<<(ostream &, const Array &);
    friend istream &operator>>(istream &, Array &);

    public:
        Array(int = 10);       // construtor padrão
        Array (const Array &); // construtor de cópia
        ~Array();
        int getSize() const; // retorna o tamanho

        //operador de atribuição
        const Array &operator=(const Array &);

        //operador de igualdade
        bool operator==(const Array &) const;

        bool operator!=(const Array &right) const {
            // irá executar operator==
            return ! (*this == right);
        }

        // retorna o endereço do dado em uma posição do array
        int &operator[](int);
        // retorna cópia do dado em uma posição do array
        int operator[](int) const;
    
    private:
        // tamanho do array
        int size;
        // ponteiro para o primeiro elemento do array
        int *ptr;
};

#endif