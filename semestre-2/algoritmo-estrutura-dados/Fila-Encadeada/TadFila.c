#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

typedef struct node {
    Node *proximo;
    char conteudo;
} Node;

typedef struct fila {
    Node *inicio;
    Node *fim;
    int tam;
} Fila;

Fila *criar() {
    Fila* fila = malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tam = 0;
    return fila;
}

void inserir(Fila *fila, char valor) {

    Node *nova;
    nova = malloc(sizeof(Node));

    nova->conteudo = valor;
    nova->proximo = NULL;

    // Se a fila estiver vazia
    if (fila->inicio == NULL) {
        fila->inicio = nova;
        fila->fim = nova;
    } else {
        fila->fim->proximo = nova;
        fila->fim = nova;
    }
    (fila->tam)++;
}

char remover(Fila *fila) {
    // Se a fila estiver vazia
    if (fila->inicio == NULL) return '\0';

    Node *paraRemover = fila->inicio;
    char valor = paraRemover->conteudo;
    
    fila->inicio = paraRemover->proximo;
    // Se o último elemento foi removido, então sobrou apenas null.
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(paraRemover);
    return valor;
}

// [  ] -> [ ] -> [ ] -> null
void imprimir(Fila *fila) {
    Node *atual;
    atual = fila->inicio;

    while (atual != NULL) {
        printf("%c ", atual->conteudo);
        atual = atual->proximo;
    }
}
