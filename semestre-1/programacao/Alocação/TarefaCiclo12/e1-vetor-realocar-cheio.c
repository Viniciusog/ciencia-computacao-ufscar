#include <stdio.h>

#include <stdlib.h>

// Aluno: Vinícius de Oliveira Guimarães



int main ()

{



    float *numeros;

    numeros = (float *) calloc(10, sizeof(float));

    

    if (numeros == NULL) {

        printf("\nErro ao alocar memória.\n");

    } else {

        int tamanhoTotalArray = 10;

        float numero;

        int indice = 0;

        

        do {

          scanf("%f", &numero);

          numeros[indice] = numero;

          indice = indice + 1;

    

          // Quando o meu array tiver cheio, iremos aumentá-lo de tamanho

          if (indice == tamanhoTotalArray) {

              // Agora o nosso array de float apontará para um espaço em memória com +10 de espaço para novos números

              numeros = realloc(numeros, (tamanhoTotalArray + 10) * sizeof(float));

              

              if (numeros == NULL) {

                  printf("\nErro ao realocar memória.\n");

              } else {

                    tamanhoTotalArray = tamanhoTotalArray + 10;

              }

          }

        } while (numero != 0);

    

        printf("\nNÚMEROS DIGITADOS:\n");

        for (int i = 0; i < tamanhoTotalArray; i++) {

            printf("%f\n", numeros[i]);

        }

        free(numeros);

    }

}