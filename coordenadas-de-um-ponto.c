#include <stdio.h>
#include <math.h>
 
//Aluno: Vinícius de Oliveira Guimarães
//Ciência da Computação
//RA: 802431

int main() {

    typedef double coordenada;

    typedef struct ponto {
        coordenada x;
        coordenada y;
    } Ponto;
 
    Ponto ponto;


    scanf("%lf %lf", &ponto.x, &ponto.y);
    
    if (ponto.x > 0 && ponto.y > 0) {
        printf("Q1\n");
    } else if (ponto.x < 0 && ponto.y > 0) {
        printf("Q2\n");
    } else if (ponto.x < 0 && ponto.y < 0) {
        printf("Q3\n");
    } else if (ponto.x > 0 && ponto.y < 0) {
        printf("Q4\n");
    } else if (ponto.x == 0 && ponto.y == 0) {
        printf("Origem\n");
    } else if (ponto.y != 0 && ponto.x == 0) {
        printf("Eixo Y\n");
    } else if (ponto.y == 0 && ponto.x != 0) {
        printf("Eixo X\n");
    }

    return 0;
}