#include <stdio.h>
#include "SelectionSort.h"

//Eficiência O(n^2)
//Ordem de memória O(1) pois usa uma variável auxiliar
void selectionSort(int v[], int n) {
    int indMin;
    int aux;
    for (int i = 0; i < n - 1; i++) {
        print(v, n);
        indMin = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[indMin]) {
                indMin = j;
            }
        }
        aux = v[i];
        v[i] = v[indMin];
        v[indMin] = aux;
    }
    print(v, n);
}

void print(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}