#include <stdio.h>
#include <stdlib.h>

void intercala(int array[], int *inversoes, int p, int q, int r) {
    int i, j, tam;
    i = p;
    j = q;
    tam = r - p;

    int *w = malloc(tam *sizeof(int));
    int k = 0;
    while (i < q && j < r) {
        if (array[i] <= array[j]) {
            w[k] = array[i];
            i++;
            k++;
        } else {
            *inversoes += q - i;
            w[k] = array[j];
            k++;
            j++;
        }
    }

    while (i < q) { w[k] = array[i]; k++; i++; }

    while (j < r) { w[k] = array[j]; k++; j++; }

    for (int k = 0; k < tam; k++) {
        array[p + k] = w[k];
    }
    free(w);
}

void mergeSort(int array[], int *inversoes, int p, int r) {
    if (r - p > 1) {
        int m  = (r + p) / 2;
        mergeSort(array, inversoes, p, m);
        mergeSort(array, inversoes, m, r);
        intercala(array, inversoes, p, m, r);
    }
}

int main() {
    int N;
    scanf("%d", &N);

    int *array = (int *) malloc(N *sizeof(int));;
    for (int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }

    int inversoes = 0;
    mergeSort(array, &inversoes, 0, N);
    for (int i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\ninversões: %d", inversoes);
}