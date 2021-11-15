/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>


float** criaMatriz(int lin, int col) {
    float ** mat;
    mat = (float **) calloc(lin, sizeof(float *));
    
    if (mat == NULL) {
        printf("Erro durante alocação de memória.");
    } else {
        for (int i = 0; i < lin; i++) {
            mat[i] = (float *) calloc(col, sizeof(float));
            
            if (mat[i] == NULL) {
               printf("Erro durante alocação de memória. Ponteiros dentro do array de ponteiros.");
            }
        }
    }
    
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
             mat[i][j] = (rand() % 101) / 10.0;
        }
    }
    
    return mat;
}

float maior(float ** m, int lin, int col) {
    float maiorNota = 0;
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            if (m[i][j] > maiorNota) { 
                maiorNota = m[i][j];
            }
        }
    }
    
    return maiorNota;
}

float media(float ** m, int lin, int col) {
    float somaMediaTodosAlunos = 0;
    
    // Para cada ponteiro dentro do vetor de ponteiros
    for (int i = 0; i < lin; i++) {
        float somaNotasAluno = 0;
        float mediaAluno;
        // Para cada float dentro do vetor de float que o ponteiro m[i] aponta
        for (int j = 0; j < col; j++) {
            somaNotasAluno = somaNotasAluno + m[i][j];
        }
        mediaAluno = somaNotasAluno / col;
        somaMediaTodosAlunos = somaMediaTodosAlunos + mediaAluno;
    }
    
    // somaMediaTodosAlunos / lin é a média geral de todos os alunos;
    return somaMediaTodosAlunos / lin;
}

float liberaMemoria(float ** m, int lin) {
    // Para cada ponteiro dentro do array de ponteiros
    for (int i = 0; i < lin; i++) {
        free(m[i]);
    }
    free(m);
}


int main()
{
    int qtdAlunos = 10;
    int qtdProvas = 4;
    
    // Minha matriz é um ponteiro que aponta para um array de ponteiros de float
    float **m = criaMatriz(qtdAlunos, qtdProvas);
    
    printf("\n-------------------------------\n");
    
    float maiorNota = maior(m, qtdAlunos, qtdProvas);
    float mediaGeral = media(m, qtdAlunos, qtdProvas);
    
    for (int i = 0; i < qtdAlunos; i++) {
        for (int j = 0; j < qtdProvas; j++) {
            printf("%fl ", m[i][j]);
        }
        printf("\n");
    }

    printf("\nMAIOR NOTA: %fl\n", maiorNota);
    printf("MEDIA GERAL: %fl", mediaGeral);
    
    liberaMemoria(m, qtdAlunos);
}
