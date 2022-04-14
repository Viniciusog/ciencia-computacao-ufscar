#include "Arvore.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int conteudo;
    Node *esq;
    Node *dir;
} Node;

Node* criar() {
    return NULL;
}

void inserir(Node **node, int valor, int *ok) {
    if (*node == NULL) {
        Node *novo = malloc(sizeof(Node));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->conteudo = valor;
        *node = novo;
        *ok = 1;
    } 
    // adicionar na esquerda
    else if ((*node)->conteudo > valor) {
        inserir(&(*node)->esq, valor, ok);
    } 
    // adicionar na direita
    else if((*node)->conteudo < valor) {
        inserir(&(*node)->dir, valor, ok);
    }
}

int estaNaArvore(Node *node, int valor) {
    if (node == NULL) {
        return 0;
    } else if (node->conteudo == valor) {
        return 1;
    } else if (node->conteudo > valor) {
        return estaNaArvore(node->esq, valor);
    } else if (node->conteudo < valor) {
        return estaNaArvore(node->dir, valor);
    }
}

Node *menorElemento(Node *node) {
    if (node == NULL) {
        return NULL;
    } else if (node->esq == NULL) {
        return node;
    } else {
        return menorElemento(node->esq);
    }
}

Node *remover(Node **node, int valor) {
    if (*node == NULL) {
        return NULL;
    } 
    //esquerda
    else if ((*node)->conteudo > valor) {
        (*node)->esq = remover(&(*node)->esq, valor);
    } 
    //direita
    else if ((*node)->conteudo < valor) {
        (*node)->dir = remover(&(*node)->dir, valor);
    } 
    //encontrou o elemento
    else if ((*node)->conteudo == valor) {
        //sem filhos
        if ((*node)->dir == NULL && (*node)->esq == NULL) {
            free(*node);
            return NULL;
        } 
        //1 filho na esq
        else if ((*node)->dir == NULL) {
            Node *filhoEsq = (*node)->esq;
            free(*node);
            return filhoEsq;
        } 
        //1 filho na dir
        else if ((*node)->esq == NULL) {
            Node *filhoDir = (*node)->dir;
            free(*node);
            return filhoDir;
        } 
        //dois filhos
        else {
            Node *menorDir = menorElemento((*node)->dir);
            (*node)->conteudo = menorDir->conteudo;
            (*node)->dir = remover(&(*node)->dir, menorDir->conteudo);
        }
    }
    return *node;
}

void inOrdem(Node *node) {
    if (node == NULL) {
        return;
    }
    inOrdem(node->esq);
    printf(" %d", node->conteudo);
    inOrdem(node->dir);
}