
#include <stdio.h>
#include<stdlib.h>

#define N 10

int posicaoNoAlfabeto(char meuChar) {
    char alfabeto[27] = {'a', 'b', 'c', 'd','e','f','g','h','i','j',
    'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    int cont;
    for (cont = 1; cont <= 27; cont++) {
        if (meuChar == alfabeto[cont]) {
            return cont;
        }
    }
} 

int main(int argc, char const *argv[])
{

    char palavra[N];
    int i, j;
    int hash = 0;

    for (j = 0; j < 5; j++) {

        scanf("%s", palavra);
        
        int asciiPosicao0  = palavra[0];
        for (i = 0; i < N; i++) {
            int ascii = palavra[i];
            hash = hash + ascii;
        }
        hash = hash - asciiPosicao0 + posicaoNoAlfabeto(palavra[0]);

        printf(" %d\n", hash);
        hash = 0;
        
    }

     

    return 0;
}
