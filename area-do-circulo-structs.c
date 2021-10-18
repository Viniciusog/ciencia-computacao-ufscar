#include <stdio.h>

int main() {

    typedef double medida;
     
    typedef struct circulo {
        medida raio;
        medida area;
    } Circulo;

    Circulo primeiroCirculo;
    double pi = 3.14159;

    scanf("%lf", &primeiroCirculo.raio);
    primeiroCirculo.area = pi * primeiroCirculo.raio * primeiroCirculo.raio;

    printf("A=%.4lf\n", primeiroCirculo.area);

    return 0;
}