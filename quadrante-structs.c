#include <stdio.h>

//Aluno: Vinícius de Oliveira Guimarães
//Ciência da Computação
//RA: 802431

int main()
{

    typedef int coordenada;
    typedef struct ponto {
        coordenada x;
        coordenada y;
    } Ponto;

    Ponto primeiroPonto;

    scanf("%i", &primeiroPonto.x);
    scanf("%i", &primeiroPonto.y);

    do {
        
        if (primeiroPonto.x > 0 && primeiroPonto.y > 0) {
            printf("primeiro\n");
        }
        if (primeiroPonto.x < 0 && primeiroPonto.y > 0) {
            printf("segundo\n");
        }
        if (primeiroPonto.x < 0 && primeiroPonto.y < 0) {
            printf("terceiro\n");
        }
        if (primeiroPonto.x > 0 && primeiroPonto.y < 0) {
            printf("quarto\n");
        }

        scanf("%i", &primeiroPonto.x);
        scanf("%i", &primeiroPonto.y);
    } while (primeiroPonto.x != 0 && primeiroPonto.y != 0 );
    
    return 0;
}