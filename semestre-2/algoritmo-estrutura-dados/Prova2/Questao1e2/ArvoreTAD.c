#include "Arvore.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int chave;
    Node *esq;
    Node *dir;
} Node;

typedef Node *ABB;

ABB criar() {
    return NULL;
}

/*
A função implementada apenas insere um valor se o mesmo não tiver
sido adicionado anteriormente.
*/
void inserir(ABB *R, int ch) {
    if ((*R) == NULL) {
        Node *novo = malloc(sizeof(Node));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->chave = ch;
        (*R) = novo;
    } else {
        if ((*R)->chave > ch) {
            //inserir na esquerda
            inserir(&(*R)->esq, ch);
        } else if ((*R)->chave < ch) {
            //inserir na direita
            inserir(&(*R)->dir, ch);
        }  
    }
}

//Imprimir inOrdem
void imprimir(ABB R) {
    if (R == NULL) {
        return;
    }
    imprimir(R->esq);
    printf("%d ", R->chave);
    imprimir(R->dir);
}

int getAltura1(Node *node) {
    if (node == NULL) {
         return 0;
    }

    int hEsq = getAltura1(node->esq) + 1;
    int hDir = getAltura1(node->dir) + 1;

    return hEsq > hDir ? hEsq : hDir;
}
