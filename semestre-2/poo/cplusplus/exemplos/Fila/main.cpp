
#include <iostream>
#include "Fila.h"

using std::endl;
using std::cout;
using std::cin;

int main() {
    Fila *f = new Fila(10);
    f->inserir('T');
    f->inserir('I');
    f->inserir('Y');
    f->remover();
    cout << "Estado da fila 1: " << f->getEstado() << endl;
    f->imprimir();
    cout << endl;
    f->Set_tamanho_maximo(20);
    cout << "Estado da fila 1 ao alterar tamanho: " << f->getEstado() << endl;

    Fila *f2 = new Fila(5);
    cout << "Total de filas instanciadas: " << f->getContadorFilas() << endl;
}