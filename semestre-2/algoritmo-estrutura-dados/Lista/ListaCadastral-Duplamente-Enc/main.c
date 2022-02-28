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

    printf("Lista cadastral: ");
    imprimir(cabeca);

    remover(cabeca, 'E');

    printf("\n");
    printf("\nLista ao remover o primeiro 'E': ");
    imprimir(cabeca);

    char maiorAscii = maiorValorASCII(cabeca);
    printf("\nMaior valor ASCII: %c", maiorAscii);

    printf("\n");
    buscaInserir(cabeca, 'B', 'R');

    printf("\nLista ao realizar 'buscaInserir': ");
    imprimir(cabeca);
}