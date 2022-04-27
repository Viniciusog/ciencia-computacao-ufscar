#include "Array.h"

using std::cerr;
using std::cout;
using std::cin;
using std::endl;

#include <iomanip>
using std::setw;

// sai do protótipo de função
#include <cstdlib>
using std::exit;

Array::Array(int arraySize) {
    size = (arraySize > 0 ? arraySize : 10);
    ptr = new int [size];

    for (int i = 0; i < size; i++) {
        ptr[i] = 0;
    }
}

//construtor de cópia
Array::Array(const Array &arrayToCopy) {
    size = arrayToCopy.size;
    ptr = new int [size];

    for (int i = 0; i < size; i++) {
        ptr[i] = arrayToCopy.ptr[i];
    }
}

Array::~Array() {
    delete [] ptr;
}

int Array::getSize() const {
    return size;
}

//retorno const evita (a1 = a2) = a3
const Array &Array::operator=(const Array &right) 
{
    //evita auto atribuição
    if (&right != this) {
        //para array de tamanhos diferentes, 
        // desaloca array do original, então aloca o novo array à esquerda
        if (size != right.size) {
            delete [] ptr;
            size = right.size;
            ptr = new int[size];
        }

        for (int i = 0; i < size; i++) {
            ptr[i] = right.ptr[i];
        }
    }

    return *this; // permite x = y = z
}

bool Array::operator==(const Array &right) const {
    if (size != right.size) {
        return false;
    }

    for (int i  = 0; i < size; i++) {
        if (ptr[i] != right.ptr[i]) {
            return false;
        }    
    }
    return true;
}

// retorna um ponteiro para o elemento de uma posição
int &Array::operator[](int subscript) {
    if (subscript < 0 || subscript >= size) {
        cerr << "\nError: subscript" << subscript 
        << " out of range" << endl;
        exit(1);
    }
    return ptr[subscript];
}

// retorna o valor do elemento 
// que está em uma determinada posição
int Array::operator[](int subscript) const {
    if (subscript < 0 || subscript >= size) {
        cerr << "\nError: subscript. " << subscript 
        << " out of range" << endl;
        exit(1);
    }
    return ptr[subscript];
}

istream &operator>>(istream &input, Array &a) {
    for (int i = 0; i < a.size; i++) {
        input >> a.ptr[i];
    }
    return input; // permite cin >> x >> y
}

ostream &operator<<(ostream &output, const Array &a)
{
    int i;
    for (i = 0; i < a.size; i++) {
        output << setw(12) << a.ptr[i];

        // 4 números por linha
        if ((i + 1) % 4 == 0) {
            output << endl;
        }
    }

    // termina a última linha de saída
    if (i % 4 != 0) {
        output << endl;
    }

    return output; // permite cout << x << y
}


