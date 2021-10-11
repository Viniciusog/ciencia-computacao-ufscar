#include <stdio.h>
#include <math.h>

float distanciaEntre2Pontos(int xA, int yA, int xB, int yB) {
     // Distância entre dois pontos 
     // d = sqrt((xA-xB)²+(yA-yB)²)
     
     float distancia = sqrt(pow(xA-xB, 2) + pow(yA-yB, 2));
     return distancia;
}


int main()
{
    int xA, xB, yA, yB;
    xA = 1;
    yA = 5;
    xB = -3;
    yB = 9;
    printf("Distância entre A e B: %fl", distanciaEntre2Pontos(xA, yA, xB, yB));
    return 0;
}