#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main() {
    Fila *fila = criar();
    inserir(fila, 'A');
    inserir(fila, 'B');
    inserir(fila, 'C');
    printf("Fila: ");
    imprimir(fila);
    printf("\nTamanho da fila: %d", fila->tam);

    printf("\n");
    char v1 = remover(fila);
    char v2 = remover(fila);

    printf("Valores removidos: %c, %c", v1, v2);
    printf("\n\nFila restante: ");
    imprimir(fila);

    printf("\nTamanho da fila restante: %d", fila->tam);
    printf("\nFila é vazia? %s", vazia(fila) == 1 ? "sim" : "não");
    destruir(fila);

    Fila *fila2 = criar();
    printf("\nFila2 é vazia? %s", vazia(fila2) == 1 ? "sim" : "não");
}