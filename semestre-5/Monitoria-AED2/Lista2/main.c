#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

int main() {

    Noh *noh = criarArvore();
    inserir(&noh, 10);
    inserir(&noh, 5);
    inserir(&noh, 3);
    inserir(&noh, 2);
    inserir(&noh, 4);
    inserir(&noh, 15);

    int result = 1;
    verificarAVL(noh, &result);
    printf("result: %d", result);

    Noh *arv2 = criarArvore();
    inserir(&arv2, 5);
    inserir(&arv2, 10);
    inserir(&arv2, 2);
    int result2 = 1;
    verificarAVL(arv2, &result2);
    printf("result2: %d", result2);
}