#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

typedef struct node Node;

typedef struct fila {
   int tam;
   Node *primeiro;
   Node *ultimo;
} Fila;

typedef struct node {
   // O conteúdo do nó da fila é um noh da árvore
   // Ou seja, estamos armazenando um noh da árvore dentro de um nó da fila.
   Noh *conteudo;
   Node *proximo;
} Node;

Fila *criarFila();
Node *criarNodeFila(Noh *conteudo);
void inserirNaFila(Fila *fila, Noh *conteudo);
void imprimirFila(Fila *fila);
Node *removerPrimeiroDaFila(Fila *fila);
void limparFila(Fila *fila);
void freeConteudoFila(Fila *fila);

#endif