#include <stdio.h>

void desloque_menor(int vet[], int tamanho) {
    int indexMenor;
    int menorValor;
    for (int i = 0; i < tamanho; i++) {
        if (i == 0) {
            menorValor = vet[0];
        }
        
        if (vet[i] < menorValor) {
            indexMenor = i;
            menorValor = vet[i];
        }
    }
    
    int aux = vet[0];
    vet[0] = vet[indexMenor];
    vet[indexMenor] = aux; 
}

int main()
{
    int vet[5] = {1, 2, 3, 4, 0};
    
    desloque_menor(vet, 5);

    for (int i = 0; i < 5; i++) {
        printf("%d ", vet[i]);
    }
    
    return 0;
}