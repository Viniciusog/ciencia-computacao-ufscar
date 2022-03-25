// #include "./Arvore.h"
#include "./Arvore.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Node *node = NULL;

    printf("Vazia? %d\n", vazia(&node));
    
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
    printf("\nVazia? %d", vazia(&node));

    Node *maiorEl = pegarMaiorElemento(&node);
    printf("\nMaior elemento: %d\n", maiorEl->conteudo);
    inOrdem(&node);

    Node *el = pegarElemento(&node, 25);
    printf("\nElemento pego: %d\n", el != NULL ? el->conteudo : -1);

    remover(&node, 7);
    inOrdem(&node);

}