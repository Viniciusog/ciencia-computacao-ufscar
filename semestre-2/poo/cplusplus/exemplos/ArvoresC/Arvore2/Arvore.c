#include "Arvore.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int conteudo;
    Node *dir;
    Node *esq;
} Node;

typedef Node *Arvore;

/* Arvore inserir(Arvore a, int valor) {
    //Se a árvore estiver vazia
    if (a == NULL) {
        Node *novo = malloc(sizeof(Node));
        novo->conteudo = valor;
        novo->dir = NULL;
        novo->esq = NULL;
        return novo;
    } else if (a->conteudo == valor) {
        return a;
    } else if (a->conteudo > valor) {
        a->esq = inserir(a->esq, valor);
    } else {
        a->dir = inserir(a->dir, valor);
    }
} */

int vazia(Node **a) {
    return (*a) == NULL ? 1 : 0;
}

void inserir(Node **a, int valor) {
    if (*a == NULL) {
        Node *novo = malloc(sizeof(Node));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->conteudo = valor;
        *a = novo;
    } else if ((*a)->conteudo > valor) {
        inserir(&(*a)->esq, valor);
    } else if ((*a)->conteudo < valor) {
        inserir(&(*a)->dir, valor);
    }
}

Node *pegarMaiorElemento(Node **a) {
    Node *atual = *a;
    while (atual != NULL && atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual;
}

Node *pegarMenorElemento(Node **a) {
    Node *atual = *a;
    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

Node *pegarElemento(Node **a, int valor) {
    if ((*a) == NULL || (*a)->conteudo == valor) {
        return *a;
    } else if ((*a)->conteudo < valor) {
        return pegarElemento(&(*a)->dir, valor);
    } else if ((*a)->conteudo > valor) {
        return pegarElemento(&(*a)->esq, valor);
    }
}

Node *remover(Node **a, int valor) {
    if ((*a) == NULL) {
        return *a;
    }
    else if ((*a)->conteudo > valor) {
        (*a)->esq = remover(&(*a)->esq, valor);
        printf("\n(*a)->esq = %d\n", (*a)->esq->conteudo);
    } else if ((*a)->conteudo < valor) {
        (*a)->dir = remover(&(*a)->dir, valor);
        printf("\n(*a)->dir = %d\n", (*a)->dir->conteudo);
    } 
    // Achamos o elemento. ((*a)->conteudo == valor)
    else {
        //1º caso, removendo elemento sem nós
        if ((*a)->dir == NULL && (*a)->esq == NULL) {
            free(*a);
            return NULL;
        } 
        // 2º caso, removendo elemento com 1 nó
        else if ((*a)->esq == NULL) {
            // Se a esquerda for nula, então retorna ponteiro da direita
            Node *temp = (*a)->dir;
            printf("\nTemp: %d\n", temp->conteudo);
            free(*a);
            return temp;
        } else if ((*a)->dir == NULL) {
            // Se a direita for nula, então retornaremos o ponteiro da esquerda
            Node *temp = (*a)->esq;
            free(*a);
            return temp;
        } else {
            // Se o nó tiver dois filhos
            Node *temp = pegarMenorElemento(&(*a)->dir);
            (*a)->conteudo = temp->conteudo;
            (*a)->dir = remover(&(*a)->dir, temp->conteudo);
        }
    }
    return *a;
}


void inOrdem(Node **a) {
    if (*a == NULL) {
        return;
    }
    inOrdem(&(*a)->esq);
    printf("(%d) ", (*a)->conteudo);
    inOrdem(&(*a)->dir);
}


int altura(Arvore a) {
    int hEsq, hDir;
    if (a == NULL) {
        return -1;
    }

    hEsq = altura(a->esq) + 1;
    hDir = altura(a->dir) + 1;

    return hEsq > hDir ? hEsq : hDir;
}