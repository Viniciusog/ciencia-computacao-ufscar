#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

int inserirElemento(int *array, int posicao, int valor, int tamanho) {
    if (posicao < tamanho) {
        array[posicao] = valor;
    }
}


int fazerRealloc(int **array, int *tamanho) {
    (*tamanho) += 10;
    *array = realloc(*array, (*tamanho)*sizeof(int));
    for (int i = (*tamanho)-10; i < (*tamanho); i++) {
        (*array)[i] = i;
    }
}

int main() {
    /* int tamanho = 10;
    int *array = (int *) malloc(tamanho * sizeof(int));
    for (int i = 0; i < tamanho; i++) {
        array[i] = i;
    }

    //inserirElemento(array, 5, 88, 10);
    fazerRealloc(&array, &tamanho);

    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    } */

    Fila *fila = criarFila();
    Noh *noh = (Noh *) malloc(sizeof(Noh));
    noh->valor = 10;

    Noh *noh2 = (Noh *) malloc(sizeof(Noh));
    noh2->valor = 20;

    inserirNaFila(fila, noh);
    inserirNaFila(fila, noh2);
    imprimirFila(fila);
    Node *nodeRemovido = removerPrimeiroDaFila(fila);
    printf("\n");
    printf("Valor do nó removido: %d\n", nodeRemovido->conteudo->valor);
    free(nodeRemovido);
    imprimirFila(fila);
    freeConteudoFila(fila);
    printf("Tamanho da fila: %d", fila->tam);
    free(fila);
}
