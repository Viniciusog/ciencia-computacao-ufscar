// #include "./Arvore.h"
#include "./Arvore.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Node *node = criar();

    printf("Vazia? %s\n", vazia(&node) == 1 ? "sim" : "não");
    
    inserir(&node, 10);
    inserir(&node, 6);
    inserir(&node, 19);
    inserir(&node, 2);
    inserir(&node, 7);
    inserir(&node, 9);
    inserir(&node, 13);
    inserir(&node, 34);
    inserir(&node, 25);

    inOrdem(&node);
    printf("\nVazia? %s\n", vazia(&node) == 1 ? "sim" : "não");

    Node *maiorEl = pegarMaiorElemento(&node);
    printf("\nMaior elemento: %d\n", maiorEl->conteudo);
    inOrdem(&node);
    
    int ok = 0;
    Node *el = pegarElemento(&node, 25, &ok);
    printf("\nPegando elemento 25: %d\n", el != NULL ? el->conteudo : -1);

    int estaNaArvore = esta_na_arvore(&node, 13);
    int estaNaArvore2 = esta_na_arvore(&node, 674);
    printf("13 está na árvore? %s\n", estaNaArvore == 1 ? "sim" : "não");
    printf("68 está na árvore? %s\n", estaNaArvore2 == 1 ? "sim" : "não");

    printf("\nRemovendo elemento 7...\n");
    remover(&node, 7);
    inOrdem(&node);

    printf("\nAltura: %d", altura(&node));
    destroi(&node);
}