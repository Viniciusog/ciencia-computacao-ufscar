#include <stdio.h>
#include <math.h>
 
//Aluno: Vinícius de Oliveira Guimarães
//Ciência da Computação

int main() {

    typedef double coordenada;

    typedef struct ponto {
        coordenada x;
        coordenada y;
    } Ponto;
 
    Ponto p1;
    Ponto p2;

    double distanciaEntreDoisPontos;

    scanf("%lf %lf", &p1.x, &p1.y);
    
    distanciaEntreDoisPontos = sqrt(pow(p2.x-p1.x, 2) + pow(p2.y-p1.y, 2));
    printf("%.4lf\n", distanciaEntreDoisPontos);

    return 0;
}