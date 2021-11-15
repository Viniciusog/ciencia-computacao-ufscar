#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    int **mat;
    
    // calloc(3, sizeof(int *)) => Está alocando memória para 3 ponteiros de inteiros, logo, 
    // teremos um array de ponteiros de inteiros
    
    // mat = (int **) => minha matriz mat é um ponteiro que aponta para um vetor de ponteiro de inteiros.
    mat = (int **) calloc(3, sizeof(int *));
    
    // Para cada item da minha matriz eu tenho que atribuir um ponteiro que aponta para um vetor de inteiros
    for (int i = 0; i < 3; i++) {
        mat[i] = (int *) calloc(4, sizeof(int));
    }
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    
    // Tenho que percorrer cada item da minha matriz (cada ponteiro que está dentro do vetor 
    // de ponteiros, que é a minha matriz) e liberar o espaço correspondente a esse item.
    // Ou seja, a função free faz com que o ponteiro nessa posição não aponte para nenhum espaço na memória
    for (int j = 0; j < 3; j++) {
        free(mat[j]);
    }
    // Fazemos com que a minha matriz, que é um ponteiro que aponta para um vetor de ponteiros, não aponte
    // mais para esse vetor de ponteiros
    free(mat);
    
    printf("Hello World");

    return 0;
}
