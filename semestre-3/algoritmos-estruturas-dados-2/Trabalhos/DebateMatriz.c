/**
 * Aluno: Vinícius de Oliveira Guimarães
 * Resolvendo o problema dos debates utilizando matriz de adjacência
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main(int argc, char *argv[])
{
    char file_name[MAX];
    FILE *entrada;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }
    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNao encontrei o arquivo! Informe o nome da instancia\n");
        exit(EXIT_FAILURE);
    }

    int instancias;
    fscanf(entrada, "%d", &instancias);

    for (int i = 0; i < instancias; i++) {
        int estudantes;
        fscanf(entrada, "%d", &estudantes);

        int matrix[estudantes][estudantes];
        for (int i = 0; i < estudantes; i++) {
            for (int j = 0; j < estudantes; j++) {
                matrix[i][j] = 0;
            }
        }
        
        for (int j = 0; j < estudantes; j++) {
            int qntEstParaPerguntar;
            fscanf(entrada, "%d", &qntEstParaPerguntar);
            
            for (int k = 0; k < qntEstParaPerguntar; k++) {
                int numeroEstudante;
                fscanf(entrada, "%d", &numeroEstudante);
                matrix[j][numeroEstudante] = 1;
            }
        }

        int possivel = 1;
        for (int l = 0; l < estudantes; l++) {
            if (!possivel) {
                break;
            }
            for (int c = 0; c < estudantes; c++) {
                int presenca = matrix[l][c];
                if (presenca) {
                    for (int w = 0; w < estudantes; w++) {
                        // C precisa ser diferente de W pois
                        // 0 pode perguntar para 4
                        // e 4 pode perguntar para 0 e mesmo as
                        if (matrix[c][w] == 1 && matrix[l][w] == 1) {
                            possivel = 0;
                            break;
                        }
                    }
                }
            }
        }

        if (possivel) { 
            printf("Vai ter debate\n"); 
        } else printf("Impossivel\n");
    }

    fclose(entrada);
    return 0;
}
