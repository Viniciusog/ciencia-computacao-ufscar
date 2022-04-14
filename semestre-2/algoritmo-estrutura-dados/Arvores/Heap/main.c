#include "Heap.h" 
#include <stdlib.h>
#include <stdio.h>

int main() {
    int v[10] = {17, 1, 5, 2, 6, 4, 3, 9, 8, 7};
    int n = 10;

    inserir(v, n, 19);
    inserir(v, n, 25);
    inserir(v, n, 18);

    imprimir(v, n);

    remover(v, n);

    printf("\nHeap após remover o elemento da raiz:");
    imprimir(v, n);

}