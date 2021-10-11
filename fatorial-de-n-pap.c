#include <stdio.h>

long long int fatorial(int numero) {
    int i;
    long long int produto=1;
    
    for (i = numero; i > 1; i--) {
        produto = produto * i;
    }

    return produto;
}

int main()
{
    
    int n, p;
    long long int resultado;
    printf("Insira o valor de n e p.\n");
    scanf("%i %i", &n, &p);
    
    resultado = fatorial(n) / (fatorial(p) * fatorial(n-p));
    printf("Fatorial de %d, %d a %d = %lld", n, p, p, resultado);
    return 0;
}