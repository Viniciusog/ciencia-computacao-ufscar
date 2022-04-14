#include "Heap.h"
#include <stdlib.h>
#include <stdio.h>

int pai(int index) {
    return (index - 1)/2;
}

int filhoEsq(int index) {
    return 2*index + 1;
}

int filhoDir(int index)  {
    return 2*index + 2;
}

void troca(int *n1, int *n2) {
    int aux = *n1;
    *n1 = *n2;
    *n2 = aux;
}

int indexMaiorFilho(int v[], int index) {
    if (v[filhoDir(index)] > v[filhoEsq(index)]) {
        return filhoDir(index);
    } else {
        return filhoEsq(index);
    }
}

// Pega o elemento que está em baixo e leva para cima até que seu pai seja maior
// ou quando chegar na raiz
void CorrigeHeapSubindo(int v[], int n) {
    int index = n - 1;

    while (index > 0 && v[pai(index)] < v[index]) {
        troca(&v[pai(index)], &v[index]);
        index = pai(index);
    }
}

//n é a posição livre
int inserir(int v[], int n, int valor) {
    v[n - 1] = valor;
    CorrigeHeapSubindo(v, n);
    return n + 1; //tamanho do array
}

void desceHeap(int v[], int n, int indexInicial) {
    int index = indexInicial;
    //enquanto existir filho e o valor do atual for menor que o valor do filho
    while (indexMaiorFilho(v, index) < n && v[index] < v[indexMaiorFilho(v,index)]) {
        int filho = indexMaiorFilho(v,index);
        troca(&v[filho], &v[index]);
        index = filho;
    }
}

// encontrar o índice do maior filho, dado um índice de um nó inicial
int remover(int v[], int n) {
    v[0] = v[9];
    desceHeap(v, n, 0);
    return n - 1;
}

void imprimir(int v[], int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf(" %d", v[i]);
    }
}