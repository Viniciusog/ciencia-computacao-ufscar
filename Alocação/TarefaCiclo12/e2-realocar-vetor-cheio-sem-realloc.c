#include <stdio.h>

#include <stdlib.h>

#include <string.h>



// Aluno: Vinícius de Oliveira Guimarães




float * alocarNumerosFloat(int tamanho) {

    float * array;

    array = (float *) calloc(tamanho, sizeof(float));

    return array;

}



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

              

              // Cria um vetor com +10 posições

              float * vetorAlocado = alocarNumerosFloat(tamanhoTotalArray + 10);

              

              if (vetorAlocado == NULL) {

                printf("\nErro ao alocar memória.\n");

              } else {

                tamanhoTotalArray = tamanhoTotalArray + 10;

                

                // Passa os números do array menor para o array maior

                for (int i = 0; i < tamanhoTotalArray; i++) {

                  vetorAlocado[i] = numeros[i];

                }

              

                free(numeros);

              

                // A partir de agora o meu array 'numeros' apontará para o novo/maior vetor de float

                numeros = vetorAlocado;

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