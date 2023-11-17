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

int calcularAltura(Noh *arvore);
int calcularAlturaIterativamente(Noh *arvore);

void imprimirArvoreInOrder(Noh *arvore);

int calcularQuantidadeNos(Noh *arvore);
void calcularQuantidadeNosInterno(Noh *arvore, int *pQtd);

void preencherPai(Noh *arvore);
void preencherPaiInterno(Noh *arvore, Noh *pai);

int verificarBinariaDeBusca(Noh *arvore);
void verificarBinariaDeBuscaInterno(Noh *arvore, int *resultado);

int * transformarArvoreEmArray(Noh *arvore, int *tamanho);
void inserirElementosArray(Noh *arvore, int **array, int *posicao, int *tamAtual);

Noh *arrayParaArvoreBalanceada(int *array, int posInicial, int posFinal);

Noh *procurarPaiDeNoh(Noh *arvore, Noh *noh);

#endif

