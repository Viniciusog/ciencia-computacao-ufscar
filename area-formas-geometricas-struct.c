#include <stdio.h>
#include <math.h>

//Aluno: Vinícius de Oliveira Guimarães
//Ciência da Computação

int main () {

    typedef double medida;

    typedef struct triangulo {
        medida alturaC;
        medida baseA;
        medida area;
    } Triangulo;

    typedef struct retangulo {
        medida ladoA;
        medida ladoB;
        medida area;
    } Retangulo;

    typedef struct circulo {
        medida raioC;
        medida area;
    } Circulo;

    typedef struct quadrado {
        medida ladoB;
        medida area;
    } Quadrado;

    typedef struct trapezio {
        medida baseA;
        medida baseB;
        medida alturaC;
        medida area;
    } Trapezio;

    Triangulo primeiroTriangulo;
    Retangulo primeiroRetangulo;
    Quadrado primeiroQuadrado;
    Circulo primeiroCirculo;
    Trapezio primeiroTrapezio;

    double a, b, c, pi=3.14159;
    scanf ("%lf %lf %lf", &a, &b, &c);

    primeiroTriangulo.alturaC = c;
    primeiroTriangulo.baseA = a;
    primeiroTriangulo.area = (primeiroTriangulo.baseA * primeiroTriangulo.alturaC) / 2;

    primeiroRetangulo.ladoA = a;
    primeiroRetangulo.ladoB = b;
    primeiroRetangulo.area = primeiroRetangulo.ladoB * primeiroRetangulo.ladoA;

    primeiroQuadrado.ladoB = b;
    primeiroQuadrado.area = pow(primeiroQuadrado.ladoB, 2);

    primeiroCirculo.raioC = c;
    primeiroCirculo.area = pi * pow(primeiroCirculo.raioC, 2);

    primeiroTrapezio.baseA = a;
    primeiroTrapezio.baseB = b;
    primeiroTrapezio.alturaC = c;
    primeiroTrapezio.area = ((primeiroTrapezio.baseA + primeiroTrapezio.baseB) * primeiroTrapezio.alturaC ) / 2;

    printf("TRIANGULO: %.3lf\n", primeiroTriangulo.area);
    printf("CIRCULO: %.3lf\n", primeiroCirculo.area);
    printf("TRAPEZIO: %.3lf\n", primeiroTrapezio.area);
    printf("QUADRADO: %.3lf\n", primeiroQuadrado.area);
    printf("RETANGULO: %.3lf\n", primeiroRetangulo.area);


    return 0;
} 