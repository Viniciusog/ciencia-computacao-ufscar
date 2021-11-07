#include <stdio.h>
#include <math.h>
 
//Aluno: Vinícius de Oliveira Guimarães
//Ciência da Computação

int main () {

    typedef double medida;

    typedef struct triangulo {
        medida ladoA;
        medida ladoB;
        medida ladoC;
    } Triangulo;

    Triangulo primeiroTriangulo;

    double a, b, c, aux;
    int isTriangulo=1;
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a > b) {
        aux = a;
        a = b;
        b = aux;
    }

    if (c > b) {
        aux = b;
        b = c;
        c = aux;
    }

    if (b > a) {
        aux = a;
        a = b;
        b = aux;
    }

    primeiroTriangulo.ladoA = a;
    primeiroTriangulo.ladoB = b;
    primeiroTriangulo.ladoC = c;

    if (primeiroTriangulo.ladoA >= (primeiroTriangulo.ladoB + primeiroTriangulo.ladoC)) {
        printf("NAO FORMA TRIANGULO\n");
        isTriangulo = 0;
    } 
    if (isTriangulo != 0) {
        if ( pow(primeiroTriangulo.ladoA, 2) == (pow(primeiroTriangulo.ladoB, 2) + pow(primeiroTriangulo.ladoC, 2))) {
            printf("TRIANGULO RETANGULO\n");
        } 
        if ( pow(primeiroTriangulo.ladoA, 2) > (pow(primeiroTriangulo.ladoB, 2) + pow(primeiroTriangulo.ladoC, 2))) {
            printf("TRIANGULO OBTUSANGULO\n");
        } 
        if ( pow(primeiroTriangulo.ladoA, 2) < (pow(primeiroTriangulo.ladoB, 2) + pow(primeiroTriangulo.ladoC, 2))) {
            printf("TRIANGULO ACUTANGULO\n");
        } 
        if (primeiroTriangulo.ladoA == primeiroTriangulo.ladoB && primeiroTriangulo.ladoA == primeiroTriangulo.ladoC) {
            printf("TRIANGULO EQUILATERO\n");
        } 
        if ((a == b && a != c) || (a == c & a != b) || (b == c && b != a)) {
            printf("TRIANGULO ISOSCELES\n");
        }
    }
    
    return 0;
}