
#include <stdio.h>
#include <stdlib.h>

//Ordenação crescente por Selection Sort
//Eficiência O(n^2)
//Ordem de memória O(1) pois usa uma variável auxiliar
int ordena(int v[], int n) {
    int aux;
    int indMin;
    for (int i = 0; i < n - 1; i++) {
        indMin = i;
        for(int j = i + 1; j < n; j++) {
            if (v[j] < v[indMin]) {
                indMin = j;
            }
        }
        //realizar a troca
        aux = v[i];
        v[i] = v[indMin];
        v[indMin] = aux;
    }
}

void print(int v[], int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
}