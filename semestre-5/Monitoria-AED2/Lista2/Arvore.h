#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct noh Noh;

typedef struct noh {
   Noh *pai;
   Noh *esq;
   Noh *dir;
   int valor;
} Noh;

Noh * criarArvore();
void inserir(Noh **arvore, int elemento);
int verificarAVL(Noh *arvore, int *result);
int calcularAltura(Noh *arvore);
void imprimirArvoreInOrder(Noh *arvore);

#endif

