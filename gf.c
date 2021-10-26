#include <stdio.h>

int main()
{
    int tamanho;
    double media;
    double soma = 0;
    double vet[tamanho];
    int i;
    
    scanf("%d", &tamanho);
    
    for (i = 0; i < tamanho; i++) {
        scanf("%lf", &vet[i]);
        
    }
    
    int j;
    for (j = 0; j < tamanho; j++) {
        soma = soma + vet[j];
    }
    
    if (tamanho > 0) {
        media = soma/tamanho;
    } else {
        media = -1;
    }
    
    printf("Media: %lf", media);
}
