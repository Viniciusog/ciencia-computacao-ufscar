#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

int main() {
    Fila *f = criar();
    inserir(f, 'J');
    inserir(f, 'A');
    inserir(f, 'R');
    inserir(f, 'H');

    remover(f);

    imprimir(f);
}