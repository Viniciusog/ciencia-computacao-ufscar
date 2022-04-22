#include <iostream>
#include "Array.h"
using std::endl;
using std::cout;
using std::cin;

int main() {
    Array integers1(7);
    Array integers2;

    cout << "Size of array1 é: "
    << integers1.getSize() 
    << "\nArray depois de inicializar: \n"
    << integers1;

    cout << "insira 17 elementos" << endl;

    cin >> integers1 >> integers2;

    cout << "-----------------------------" << endl;
    cout << integers1 << endl;
    cout << "-----------------------------" << endl;
    cout << integers2 << endl;

    if (integers1 == integers2) {
        cout << "São iguais" << endl;
    } 

    if (integers1 != integers2) {
        cout << "São diferentes" << endl;
    }

    cout << integers1[ 6 ] << endl;
    cout << integers2[ 4 ] << endl;

    integers1[5] = 10;
    cout << integers1[5] << endl;

    cout << "-------------------" << endl;
    cout << integers1 << endl;

    // tentando acessar fora do intervalo
    cout << integers1[56] << endl;

}