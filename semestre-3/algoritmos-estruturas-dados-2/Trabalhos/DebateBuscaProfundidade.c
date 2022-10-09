/**
 * Aluno: Vinícius de Oliveira Guimarães
 * Resolvendo o problema do debate utilizando lista ligada e busca em profundidade
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct node Node;
typedef struct node {
    int key;
    Node *next;
} Node;

void inserir(Node **node, int key) {
    Node *newNode = (Node *) malloc(sizeof(Node *));
    newNode->key = key;
    newNode->next = NULL;

    if ((*node) == NULL) {
        *node = newNode;
    } else {
        newNode->next = (*node)->next;
        (*node)->next = newNode;
    }
}

void chamadaRecursiva(Node **nohLista, int visitados[], int cores[], int noh, int estudantes, int *res) {
    visitados[noh] = 1;
    Node *atual = nohLista[noh];
    while (atual != NULL) {
        if (cores[atual->key] == cores[noh]) {
            *res = 0;
        } else if (visitados[atual->key] == 0) {
            if (cores[atual->key] == -1) {
                cores[atual->key] = !cores[noh];
            }  
            chamadaRecursiva(nohLista, visitados, cores, atual->key, estudantes, res);
        }
        atual = atual->next;
    }
}

void chamada(Node **nohLista, int visitados[], int estudantes) {    
    int *cores = (int *) malloc(estudantes * sizeof(int *));
    for (int i = 0; i < estudantes; i++ ){
        cores[i] = -1;
    }

    int res = 1;
    for (int i = 0; i < estudantes && res; i++) {
        if (visitados[i] == 0) {
            visitados[i] = 1;
            cores[i] = 0;
            // realizar chamada recursiva a partir desse nó
            chamadaRecursiva(nohLista, visitados, cores, i, estudantes, &res);
        }
    } 
    if (res) {
        printf("Vai ter debate\n");
    } else {
        printf("Impossivel\n");
    }
    free(cores);
}

void freeLista(Node **noh) {
    while((*noh) != NULL) {
        Node *paraRemover = *noh;
        (*noh) = paraRemover->next;
        free(paraRemover);
    }
}

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

        int *visitados = (int *) calloc(estudantes, sizeof(int));
        Node **nohLista = (Node **) malloc(estudantes * sizeof(Node *));

        for (int i = 0; i <estudantes; i++) {
            nohLista[i] = NULL;
        }
        
        for (int j = 0; j < estudantes; j++) {
            int qntEstParaPerguntar;
            fscanf(entrada, "%d", &qntEstParaPerguntar);
            
            for (int k = 0; k < qntEstParaPerguntar; k++) {
                int numeroEstudante;
                fscanf(entrada, "%d", &numeroEstudante);
                inserir(&nohLista[j], numeroEstudante);
                inserir(&nohLista[numeroEstudante], j);
            }
        }

        chamada(nohLista, visitados, estudantes);
        
        for (int k = 0; k < estudantes; k++){
            freeLista(&nohLista[k]);
        }
        free(nohLista);
        free(visitados);
    }
    fclose(entrada);
    return 0;
}