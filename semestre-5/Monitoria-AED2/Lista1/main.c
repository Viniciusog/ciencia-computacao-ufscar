#include <stdlib.h>
#include <stdio.h>
#include "Arvore.h"

int main() {

    Noh *arvore = criarArvore();
    inserir(&arvore, 10);
    inserir(&arvore, 5);
    inserir(&arvore, 3);
    inserir(&arvore, 8);
    inserir(&arvore, 20);
    inserir(&arvore, 15);
    inserir(&arvore, 25);
    inserir(&arvore, 22);


    //printf("%d %d %d", arvore->valor, arvore->esq->valor, arvore->dir->valor);
    imprimirArvoreInOrder(arvore);

    /* printf("\n%d ", calcularAltura(arvore));

    printf("\n%d ", calcularQuantidadeNos(arvore));

    preencherPai(arvore);

    printf("\n");
    imprimirArvoreInOrder(arvore);

    int tamanho;
    int *array = transformarArvoreEmArray(arvore, &tamanho);
    printf("\nImprimindo array\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }

    printf("\n Array para árvore balanceada: \n");
    int arrayInicial[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    Noh *arvoreGerada = arrayParaArvoreBalanceada(arrayInicial, 0, 11);
    imprimirArvoreInOrder(arvoreGerada);

    Noh *arvore2 = criarArvore();
    inserir(&arvore2, 50);
    inserir(&arvore2, 30);
    inserir(&arvore2, 70);
    inserir(&arvore2, 20);
    inserir(&arvore2, 40);
    inserir(&arvore2, 60);
    inserir(&arvore2, 80);
    inserir(&arvore2, 15);
    inserir(&arvore2, 25);
    inserir(&arvore2, 35);
    inserir(&arvore2, 45);
    inserir(&arvore2, 36);

    Noh * noh45 = arvore2->esq->dir->dir;

    imprimirArvoreInOrder(arvore2);
    Noh * paiDoNoh45 = procurarPaiDeNoh(arvore2, noh45);
    if (paiDoNoh45 != NULL) {
        printf("\nValor do pai do noh 45: %d", paiDoNoh45->valor);
    } else {
        printf("\nPai do noh 45 é NULL");
    } */

    int altura = calcularAlturaIterativamente(arvore);
    printf("\nAltura: %d ", altura);
}