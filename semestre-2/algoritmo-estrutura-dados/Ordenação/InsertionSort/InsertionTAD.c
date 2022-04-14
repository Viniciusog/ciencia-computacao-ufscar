#include "Insertion.h"
#include "stdio.h"

/*
Iremos ordenar os elementos de um array apartir da posição 1 fazendo o seguinte algoritmo:
- j vai receber a posição do elemento a ser ordenado
- i recebe j - 1
- enquanto o valor que está em aux for menor do que a do elemento da posição i, iremos
colocar na posição i + 1, o elemento da posição i
- repetir o processo enquanto i for maior ou igual a zero e enquanto aux for menor do que o elemento
na posição i
*/

/*
    Eficiência: O(n^2)
    No melhor caso a eficiência é de O(n), pois o vetor já estará ordenado, não executando o for interno.
    Ordem de memória: O(1), pois usa apenas uma variável auxiliar
*/
void insertionSort(int v[], int n) {
    int i, j, aux;
    for (j = 1; j < n; j++) {   
        aux = v[j];
        for (i = j - 1; i >= 0 && aux < v[i]; i--) {
            v[i + 1] = v[i];
        }
        v[i + 1] = aux;
        print(v, n);
        printf("\n");
    }
    printf("\n");
}

void insertionSortMelhorado1(int v[], int n) {
    // realizar bubble sort para colocar o menor elemento no início
    int aux;
    for (int i = n - 1; i > 0; i--) {
        if (v[i] < v[i-1]) {
            aux = v[i-1];
            v[i-1] = v[i];
            v[i] = aux;
        }
    }

    //insertion sort padrão
    int i;
    for (int j = 2; j < n; j++) {
        aux = v[j];
        for(i = j - 1; i >= 0 && aux < v[i]; i--) {
            v[i+1] = v[i];
        }
        v[i+1] = aux;
    }
}

void print(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}