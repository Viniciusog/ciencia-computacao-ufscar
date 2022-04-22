#include "./Arvore.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

    Node *arvore = criar();
    int ok;
    inserir(&arvore, 35, &ok);
    inserir(&arvore, 27, &ok);
    inserir(&arvore, 49, &ok);
    Remove(&arvore, 35, &ok);
    inOrdem(arvore);
    inserir(&arvore, 34, &ok);
    printf("\n");
    inOrdem(arvore);
}