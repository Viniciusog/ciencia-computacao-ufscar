#include <stdio.h>



#include <stdlib.h>

#include <math.h>

// Aluno: Vinícius de Oliveira Guimarães



int ** criarMatriz(int lin, int col) {


    int ** mat;

    // A matriz é um ponteiro que aponta para um array de ponteiros de inteiros

    mat = (int **) calloc(lin, sizeof(int *));



    if (mat == NULL) {

        printf("Erro ao alocar espaço na memória.");

    } else {

        // Para cada ponteiro de inteiros sendo do array, apontaremos o ponteiro de inteiro para um vetor de inteiros

        for (int i = 0; i < lin; i++) {

            mat[i] = (int *) calloc(col, sizeof(int));

            if (mat[i] == NULL) {

                printf("Erro ao alocar espaço na memória.");

            }

        }



        // Coloca número aleatório dentro de cada posição do array de inteiros

        for (int i = 0; i < lin; i++){

            for (int j = 0; j < col; j++) {

                mat[i][j] = rand() % 10;

            }

        }

        return mat;

    }

}







void imprimirMatriz(int ** mat, int lin, int col) {

    for (int i = 0; i < lin; i++) {

        for (int j = 0; j < col; j++) {

            printf("%*d", lin, mat[i][j]);

        }

        printf("\n");

    }

}



void liberaMatriz(int ** mat, int lin) {

    for (int i = 0; i < lin; i++) {

        free(mat[i]);

    }

    free(mat);

}



        

int main() {

    

    int tamanho = 1;

    

    do {

        scanf("%d", &tamanho);

        

        int ** mat = criarMatriz(tamanho, tamanho);

        

        // Quando i é 0, j é 0 e j vai até n+i

        // Então, quando i = 0, iremos imprimir 2^0 2^1 2^2 2^3 2^4

        // Quando i = 1, j também começa em 1. Então iremos imprimir 2^1 2^2 2^3 2^4 2^5

        // Quando i = 2, j é 2 e iremos imprimir: 2^2 2^3 2^4 2^5 2^6

        // Quando i = 3, j é 3 e iremos imprimir: 2^2 2^3 2^4 2^5 2^6

        for (int i = 0; i < tamanho; i++) {

            for (int j = i; j < tamanho+i; j++) {

                // Tem que colocar j-i, pois o j começa recebendo o valor de i.

                // Nesse caso, quando tivermos i = 3, nosso j começará com 3; porém quando j = 3, estamos colocando

                // o resultado na linha 3, coluna 0, ou seja linha 3, coluna 3-i = 3-3 = 0

                mat[i][j-i] = (int) pow(2, j);

            }

        }

        

        imprimirMatriz(mat, tamanho, tamanho);

        printf("\n");

        

        liberaMatriz(mat, tamanho);

        

    } while (tamanho != 0);

}