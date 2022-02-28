#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int main() {
    Node *cabeca = criar();

    inserir(cabeca, 'J');
    inserir(cabeca, 'E');
    inserir(cabeca, 'Y');
    inserir(cabeca, 'B');
    inserir(cabeca, 'H');
    inserir(cabeca, 'E');

    imprimir(cabeca);

    remover(cabeca, 'E');

    printf("\n");
    imprimir(cabeca);

    char maiorAscii = maiorValorASCII(cabeca);
    printf("\n%c", maiorAscii);

    printf("\n");
    buscaInserir(cabeca, 'B', 'R');
    imprimir(cabeca);
}