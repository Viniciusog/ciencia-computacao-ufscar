#include <stdio.h>

int palindromo (char vetor[], int quantidade) {

   int isPalindromo = 1;
   int cont = quantidade-1;
    for (int j = 0; j < quantidade; j++) {
        if (vetor[j] != vetor[cont]) {
            isPalindromo = 0;
        }
        cont--;
    }

    return isPalindromo;
}

int main(int argc, char const *argv[])
{
    char meuArray[10];
    scanf("%s", meuArray);

    printf("É? %d", palindromo(meuArray, 9));
    return 0;
}
