#include "Heap.h"
#include <stdlib.h>
#include <stdio.h>

#define pai(i) ((i - 1) / 2)
#define fesq(i) (i * 2 + 1)
#define fdir(i) (i * 2 + 2)  

int isHeap(int v[], int lastPos) {
    int indiceAtual;
    for (int i = lastPos; i >= 0; i--) {
        indiceAtual = i;
        while (indiceAtual != 0 && v[pai(indiceAtual)] >= v[indiceAtual]) {
            indiceAtual = pai(indiceAtual);
        }
        // Ao sair do while, chegaremos na raiz, ou então 
        // o pai do elemento atual é menor que o elemento atual
        if (indiceAtual != 0 && v[pai(indiceAtual)] < v[indiceAtual]) {
            return 0;
        }
    }
    return 1;
}