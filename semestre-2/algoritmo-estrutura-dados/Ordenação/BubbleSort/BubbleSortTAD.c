#include <stdio.h>
#include "BubbleSort.h"

/**
Percorre cada um dos elementos e verifica se o anterior é maior que o atual.
Se o anterior for maior do que o atual, então trocamos os elementos.

Pega o maior elemento de cada passada do for e coloca no final do array.
*/

void bubbleSortT(int v[], int n) {
    for (int j = 0; j < n; j++) {
        for (int i = 1; i  < n - j; i++) {
            if (v[i - 1] > v[i]) {
                int aux = v[i];
                v[i] = v[i-1];
                v[i - 1] = aux;
            }
        }
    }
}

void bubbleSort(int v[], int n) {
    int trocou = 0;
    for (int j = 0; j < n; j++) {
        trocou = 0;
        print(v, n);
        for (int i = 1; i < n - j; i++) {
            if (v[i - 1] > v[i]) {
                trocou = 1;
                int aux = v[i];
                v[i] = v[i-1];
                v[i-1] = aux;
            }
        }
        // Se não houve troca durante a passagem pelos elementos do vetor, então significa que o vetor
        // já está ordenado
        if (trocou == 0) {
            break;
        }
    }
}

void bubbleSortMenorElementoInicio(int v[], int n) {
    for (int i = n; i > 0; i--) {
        if (v[i] < v[i-1]) {
            int aux = v[i - 1];
            v[i - 1] = v[i];
            v[i] = aux;
        }
    }
}

void bubbleSortMaiorElementoFim(int v[], int n) 
{
    int aux;
    for (int i = 1; i < n; i++) {
        if (v[i - 1] > v[i]) {
            aux = v[i];
            v[i] = v[i-1];
            v[i-1] = aux;
        }
    }
}

// Pega o menor elemento do vetor e coloca no início através do bubblesort
void bubbleSortMenorInicio(int v[], int n) {
    int aux;
    for (int i = n-1; i > 0; i--) {
        if (v[i] < v[i-1]) {
            aux = v[i-1];
            v[i-1] = v[i];
            v[i] = aux;
        }
    }
}

void print(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}
