#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main() {
    Fila *fila = criar();

    inserir(fila, 65);
    inserir(fila, 98);
    inserir(fila, 87);
    inserir(fila, 35);
    inserir(fila, 17);
    inserir(fila, 49);

    // A fila terá os elementos em ordem
    // Quem está no início da fila tem valor maior
    imprimir(fila);
}