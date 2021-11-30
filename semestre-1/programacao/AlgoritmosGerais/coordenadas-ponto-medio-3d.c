#include <stdio.h>
#include <math.h>

void calcularCoordenadasPontoMedio3D(float *xA, float *yA, float *zA, 
float *xB, float *yB, float *zB, float *xPm, float *yPm, float *zPm) {
     // Distância entre dois pontos 
     // d = sqrt((xA-xB)²+(yA-yB)²)
     
     *xPm = (*xA + *xB) / 2;
     *yPm = (*yA + *yB) / 2;
     *zPm = (*zA + *zB) / 2;
}

void leiaCoordenadaPonto(float *ponteiroX, float *ponteiroY, float *ponteiroZ) {
    printf("Insira as coordenadas do ponto qualquer. (x, y, z)\n");
    scanf("%f %f %f", ponteiroX, ponteiroY, ponteiroZ);
}


int main()
{
    float xA, yA, zA, xB, yB, zB;
    float xPontoMedio, yPontoMedio, zPontoMedio;
    // vai ler as coordenadas do ponto e atribuir para o endereço de memória correspondente
    
    leiaCoordenadaPonto(&xA, &yA, &zA);
    leiaCoordenadaPonto(&xB, &yB, &zB);
    
    calcularCoordenadasPontoMedio3D(&xA, &yA, &zA, &xB, &yB, &zB, &xPontoMedio, &yPontoMedio, &zPontoMedio);
    
    printf("Coordenadas do ponto médio= x:%f, y:%f, z:%f", xPontoMedio, yPontoMedio, zPontoMedio);
    
    return 0;
}