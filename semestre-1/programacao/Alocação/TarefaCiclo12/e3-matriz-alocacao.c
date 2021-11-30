#include <stdio.h>

#include <stdlib.h>



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

            printf("%d ", mat[i][j]);

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

    

    int ** mat;

    int lin;

    int col;

    

    int continuar = 1;

    

    do {

        printf("Insira a qtd de linhas da matriz: ");

        scanf("%d", &lin);

        printf("Insira a qtd de colunas da matriz: ");

        scanf("%d", &col);

        

        mat = criarMatriz(lin, col);

        

        imprimirMatriz(mat, lin, col);

        

        liberaMatriz(mat, lin);

        

        printf("\nContinuar? (Não = -1)");

        scanf("%d", &continuar);

    } while (continuar != -1);

}