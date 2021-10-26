#include <stdio.h>

int verifica_caso(char *vetor) {
    int temMaiuscula = 0, temMinuscula = 0;
    int tamanhoVetor = sizeof(*vetor)/sizeof(vetor[0]);

    int cont = 0;
    char c = 'l';
    while (c != '$') {
        if (temMaiuscula == 0) {
            int asciiM = vetor[cont];
            if (asciiM >= 65 && asciiM <= 90) {
                temMaiuscula = 1;
            }
        }
        if (temMinuscula == 0) {
            int asciim = vetor[cont];
            if (asciim >= 97 && asciim <= 122) {
                temMinuscula = 1;
            }
        }
        cont++;
        c = vetor[cont];
    }
        
    
    return temMinuscula && temMaiuscula;
}

int main(int argc, char const *argv[])
{
    char vetor[10];
    scanf("%s", vetor);
    printf("\n%d\n", verifica_caso(vetor));

    return 0;
}
