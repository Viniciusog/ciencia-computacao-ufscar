#include <stdio.h>

void limite(int *ponteiroNumero) {
    // Se o valor que está no endereço contido pelo ponteiroNumero for menor que 0,
    // então seta no endereço que está contido pelo ponteiroNumero o valor 0
    if (*ponteiroNumero < 0) {
        *ponteiroNumero = 0;
    } else if (*ponteiroNumero > 10) {
        *ponteiroNumero = 10;
    }
}

// Recebe o ponteiro número
void leia(int *numero) {
    // Lê um valor passando o ponteiro número
    scanf("%d", numero);
    // Faz o limite passando o ponteiro número
    limite(numero);
}

int main()
{
    int numero;
    leia(&numero);
    
    printf("%d", numero);
    return 0;
}