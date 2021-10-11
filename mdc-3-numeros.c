#include <stdio.h>

int min(int x, int y) {
    return (x < y) ? x : y;
}

int mdc2(int a, int b) {
     int menorNumero;
     menorNumero = min(a, b);
     int maiorDivisorComum = 1;
     
     for (int i = 1; i <= menorNumero; i++) {
         if ((a % i == 0) && (b % i == 0)) {
             if (i > maiorDivisorComum) {
                 maiorDivisorComum = i;
             }
         } 
     }
     
     return maiorDivisorComum;
}

int mdc3(int a, int b, int c) {
    int r = mdc2(a, b);
    int mdcGeral = mdc2(c, r);
    return mdcGeral;
}


int main()
{
    printf("MDC É: %d", mdc3(21, 7, 14));
    return 0;
}