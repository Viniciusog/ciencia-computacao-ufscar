#include <stdio.h>
#include <math.h>

int main () {

    typedef double medida;

    typedef struct esfera {
        medida raio;
        medida volume;
    } Esfera;

    Esfera primeiraEsfera;
    double pi = 3.14159;

    scanf("%lf", &primeiraEsfera.raio);

    primeiraEsfera.volume = (4.0 * pi * pow(primeiraEsfera.raio, 3)) / 3;

    printf("VOLUME = %.3lf\n", primeiraEsfera.volume);

    return 0;
}