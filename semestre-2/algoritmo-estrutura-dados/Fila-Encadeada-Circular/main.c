#include <stdio.h>
#include <stdlib.h>
//#include "fila.h"
#include "TadFila.c"

int main() {
    Fila *fila = criar();
    inserir(fila, 'A');
    inserir(fila, 'B');
    inserir(fila, 'C');
    imprimir(fila);
    printf("\nTamanho: %d", fila->tam);

    printf("\n");
    char v1 = remover(fila);
    char v2 = remover(fila);
    char v3 = remover(fila);

    printf("Valores: %c, %c, %c", v1, v2, v3);
    printf("\nFila: ");
    imprimir(fila);
    printf("\nTamanho: %d", fila->tam);
    destruir(fila);
}