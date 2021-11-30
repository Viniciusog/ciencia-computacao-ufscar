#include <stdio.h>

#include <stdlib.h>

#include <math.h>


// Aluno: Vinícius de Oliveira Guimarães


struct aluno {

    int matricula;

    char sobrenome[30];

    char dataNascimento[10];

};

        

int main() {

    

    int qtdAlunos;

    

    printf("Insira a quantidade de alunos para serem cadastrados: ");

    scanf("%d", &qtdAlunos);

    

    // Meu pAlunos é um ponteiro que aponta para um vetor 'struct alunos'

    struct aluno * pAlunos;

    

    pAlunos = (struct aluno *) malloc(qtdAlunos * sizeof(struct aluno));

    

    if (pAlunos == NULL) {

        printf("Erro ao alocar memória.");

    } else {

        // Lê os alunos

        for (int i = 0; i < qtdAlunos; i++) {

            printf("\n");

            printf("---- %dº ALUNO ----\n", (i+1));

            printf("Insira a matrícula: \n");

            scanf("%d", &pAlunos[i].matricula);

            printf("Insira o sobrenome: \n");

            scanf("%s", pAlunos[i].sobrenome);

            printf("Insira a data de nascimento: \n");

            scanf("%s", pAlunos[i].dataNascimento);

        }

    

        // Mostra os alunos

        printf("\n");

        for (int i = 0; i < qtdAlunos; i++) {

            printf("---- %dº ALUNO ----\n", (i+1));

            printf("Matrícula: %d \n", pAlunos[i].matricula);

            printf("Sobrenome: %s \n", pAlunos[i].sobrenome);

            printf("Data de nascimento: %s\n", pAlunos[i].dataNascimento);

            printf("\n");

        }

        

        free(pAlunos);

    }

}