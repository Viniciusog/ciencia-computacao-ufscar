#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int charNumberToIntNumber(char numero[], int tam) {
    char zero = '0';

    int base = 10;
    int cont = 0;
    int numeroTotal = 0;
    for (int i = tam - 1; i >= 0; i--) {
            // Aqui teremos o número para conseguir calcular
            int subtracao = numero[i] - zero;
            
            // Quantidade de vezes que teremos que multiplicar o número 10
            int elevado = 1;
            for (int j = 0; j < cont; j++) {
                elevado *= base;
            }

            numeroTotal += subtracao * elevado;
            // Para cada dígito dentro do array de char, a posição irá influenciará
            // no valor que será multiplicado para cada dígito
            cont++;
    }
    return numeroTotal;
}


int main() {

    char c;

    int nPalavras;
    scanf("%d", &nPalavras);

    int tamanhos[nPalavras];
    int pontosCadaPalavra[nPalavras];

    int qtdAlunos;
    scanf("%d", &qtdAlunos);

    char **palavras = (char **) malloc(nPalavras *sizeof(char *));
    for (int i = 0; i < nPalavras; i++) {
        tamanhos[i] = 1;
        palavras[i] = (char *) malloc(1 * sizeof(char));
    }

    int indiceAtual = 0;
    for (int i = 0; i < nPalavras; i++) {
        if (i == 0) {
            scanf("%c", &c);
        }
        
        do {
            scanf("%c", &c);
            if (c != '\n') {
                    if (indiceAtual >= tamanhos[i]) {
                        //printf("Aqui 1\n");
                        palavras[i] = (char *) realloc(palavras[i], (tamanhos[i]+1)*sizeof(char));
                        tamanhos[i] = tamanhos[i] + 1;
                        if (palavras[i] == NULL) {
                            printf("Tam: %d\n", tamanhos[i]);
                            printf("indiceAtual: %d\n", indiceAtual);
                            printf("Erro ao alocar memória para a palavra %d.\n", i);
                        }
                    } 
                    printf("%c ", c);
                    palavras[i][indiceAtual] = c;
                    indiceAtual++; 
            } else {
                printf("\ndigitou barra n\n");
            }
        } while (c != '\n');
        printf("\n");

        // ['A', 'B', '\0']; aqui: tam = 3, indiceAtual = 3;
        // Imprimir até tamanho - 1, pois a última posição contém na verdade o caractere \0
        for (int j = 0; j < tamanhos[i]; j++) {
            printf("%c ", palavras[i][j]);
        }
        printf("\n");
        indiceAtual = 0;
    }

    printf("Imprimindo todas as palavras: \n");

    for (int i = 0 ; i < nPalavras; i++) {
        for (int j = 0; j < tamanhos[i]; j++) {
            printf("%c ", palavras[i][j]);
        }
        printf("\n");
        //free(palavras[i]);
    }
    
    char array[] = {'1', '2', '3', '4'};
    int numeroEncontrado = charNumberToIntNumber(array, 4 );
    printf("Número encontrado pelo cálculo de número char para um número inteiro: %d", numeroEncontrado);
    

    for (int i = 0; i < nPalavras; i++) {
        free(&palavras[i]);
    }
    free(palavras);
    return 0;
}