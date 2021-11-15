/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    // ALOCA 10 * 4 BYTES NA MEMÓRIA
    /*
    int *p; // Ponteiro de inteiros, que funcionará como sendo o meu array
    p = (int *) malloc(10 * sizeof(int));
    
    if (p == NULL) {
         printf("Erro na alocação de memórica. Memória insuficiente.");
    } else {
        for (int i = 0; i < 10; i++) {
            scanf("%d", &p[i]);
        }
        
        printf("\n");
        for (int i = 0; i < 10; i++) {
            printf("%d\n", p[i]);
        }
    }
    
    printf("Hello World");

    return 0;*/
    
    //ALOCA 10 * 4 BYTES NA MEMÓRIA E INICIALIZA TODAS AS POSIÇÕES COM 0
    /*int *p;
    p = (int *) calloc(10, sizeof(int));
    
    if (p == NULL) {
        printf("Erro ao alocar memória. Memória insuficiente.");
    } else {
        for (int i = 0; i < 10; i++) {
            scanf("%d", &p[i]);
        }
        
        printf("\n");
        for (int i = 0; i < 10; i++) {
            printf("%d\n", p[i]);
        }
    }*/
    
    
    /*int *p;
    // Aloca 40 posições e seta o endereço da primeira posição no meu ponteiro p
    p = (int *) malloc(40 * sizeof(int)); 
    
    // Todas as 10 posições são inicializadas com 0
    p = (int *) calloc(10, sizeof(int)); 
    
    // Estamos realocando o meu array, dizendo que agora ele terá apenas 3 posições
    p = realloc(p, 3 * sizeof(int));
    */

    
    // REALOCA O TAMANHO DE UM PONTEIRO DE INTEIROS - REALLOC
    /*int * p;
    p = (int *) malloc(40 * sizeof(int));
    
    for (int i = 0; i < 40; i++) {
        p[i] = i + 1;
    }
    
    for (int j = 0; j < 40; j++) {
        printf("%d ", p[j]);
    }
    
    
    p = realloc(p, 3 * sizeof(int));
    
    printf("\n");
    for (int j = 0; j < sizeof; j++) {
        printf("%d ", p[j]);
    }*/
    
    
    int *p;
    p = (int *) malloc(10 * sizeof(int));
    
    for (int i = 0; i < 10; i++) {
        p[i] = i + 1;
    }
    
    printf("\n");
    for (int j = 0; j < 10; j++) {
        printf("%d ", p[j]);
    }
    
    free(p);
     
}