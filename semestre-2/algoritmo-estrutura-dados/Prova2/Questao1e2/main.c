
#include <stdlib.h>
#include "./Arvore.h"
#include <stdio.h>

int main() {
    ABB arvore = criar();

    inserir(&arvore, 11);
    inserir(&arvore, 7);
    inserir(&arvore, 70);
    inserir(&arvore, 3);
    inserir(&arvore, 9);
    inserir(&arvore, 90);

    imprimir(arvore);

    int alturaArvore = getAltura1(arvore);
    printf("\nAltura da árvore: %d", alturaArvore);
}