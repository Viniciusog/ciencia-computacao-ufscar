#include "./Array.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct array {
    int valores[10];
} Array;

Array *criar() {
    Array *a = malloc(sizeof(Array));
    for (int i = 0; i < 10; i++) {
        a->valores[i] = i+1;
    }
    return a;
} 

void imprimir(Array *a) {
    printf("\n");
    for(int i = 0 ; i < 10; i++) {
        printf("%d ", a->valores[i]);
    }
    printf("\n");
}

// Retorna a posição do elemento dentro do array ordenado
int buscaSequencial(Array *a, int valor) {
    int i = 0;

    while(i < 10 && a->valores[i] < valor) {
        i++;
    }
    // Ao chegar aqui, pode ser que achamos o valor, ou ele não está dentro do array.
    if (a->valores[i] == valor) {
        return i;
    }
    return -1;
}

int executarBuscaBinaria(Array *a, int valor) {
    //return buscaBinaria(&(*a), 0, 10 - 1, valor);
    return buscaBinaria(a, 0, 10 - 1, valor);
}   

// Retorna a posição do valor dento do array
// e => limite inferior
// d => limite superir
int buscaBinaria(Array *a, int e, int d, int valor) {
    if (d < e) {
        return -1;
    }

    int m = (e + d) / 2;

    if (a->valores[m] == valor) {
        return m;
    } else if (a->valores[m] > valor) {
        //return buscaBinaria(&(*a), e, m-1, valor);
        return buscaBinaria(a, e, m-1, valor);
    } 
    //return buscaBinaria(&(*a), m+1, d, valor);
    return buscaBinaria(a, m+1, d, valor);
}