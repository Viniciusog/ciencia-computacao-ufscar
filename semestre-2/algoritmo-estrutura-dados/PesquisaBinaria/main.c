#include "./Array.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Array *a = criar();
    imprimir(a);

    int posicaoSeq = buscaSequencial(a, 5);
    int posicaoBin = executarBuscaBinaria(a, 7);

    printf("A posição do dado - Busca sequencial: %d\n", posicaoSeq);
    printf("A posição do dado - Busca sequencial: %d", posicaoBin);
}