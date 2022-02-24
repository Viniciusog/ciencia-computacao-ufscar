#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

typedef struct node {
    char conteudo;
    Node *proximo;
} Node; 

Node * create() {
    Node * cabeca;
    cabeca = malloc(sizeof(Node));
    cabeca->proximo = NULL;
    return cabeca;
}

Node * push(Node *cabeca, char valor) {
    Node * novo;
    novo = malloc(sizeof(Node));
    novo->conteudo = valor;
    novo->proximo = cabeca->proximo;
    cabeca->proximo = novo;
    return novo;
}

char pop(Node *cabeca) {
    Node * nodeRemover = cabeca->proximo;
    char valor = nodeRemover->conteudo;
    cabeca->proximo = nodeRemover->proximo;
    free(nodeRemover);
    return valor;
}

int isEmpty(Node *cabeca) {
    return cabeca->proximo == NULL ? 1 : 0;
}

int size(Node  *cabeca) {
    Node * cabecaAux;
    cabecaAux = create();

    int qtd = 0;

    while(!isEmpty(cabeca)) {
        char valor = pop(cabeca);
        push(cabecaAux, valor);
        qtd++;
    }

    while(!isEmpty(cabecaAux)) {
        char valor = pop(cabecaAux);
        push(cabeca, valor);
    }

    free(cabecaAux);
    return qtd;
}


void print(Node * cabeca) {
    Node * cabecaAux;
    cabecaAux = create();

    while(!isEmpty(cabeca)) {
        char valor = pop(cabeca);
        push(cabecaAux, valor);
    }

    while(!isEmpty(cabecaAux)) {
        char valor = pop(cabecaAux);
        push(cabeca, valor);
        printf("%c ", valor);
    }

    free(cabecaAux);
}



