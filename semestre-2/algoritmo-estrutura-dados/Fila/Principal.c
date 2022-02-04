
#include <stdio.h>
#include <stdlib.h>

#include "fila.h"


int main() {

    Fila * f2;
    f2 = criarFila();

    inserirNaFila(f2, 'V');
    inserirNaFila(f2, 'I');
    inserirNaFila(f2, 'N');
    inserirNaFila(f2, 'I');
    inserirNaFila(f2, 'C');
    inserirNaFila(f2, 'I');
    inserirNaFila(f2, 'U');
    inserirNaFila(f2, 'S');

    printf("\nFILA INICIAL: ");
    imprimirFila(f2);

    printf("\nTamanho da fila: %d", tamanhoFila(f2));
    
    printf("\nORDENAÇÃO DA FILA: \n");
    // Ordenação na ordem descrecente.
    printf("Decrescente: ");
    ordenarFila(f2, 0);
    imprimirFila(f2);
    printf("\nCrescente: ");
    ordenarFila(f2, 1);
    imprimirFila(f2);

    printf("\nValor final da fila: \n");
    imprimirFila(f2);

    printf("\n\n---Verificando se duas filas são iguais---\n");
    Fila *f3;
    f3 = criarFila();

    inserirNaFila(f3, 'G');
    inserirNaFila(f3, 'U');
    inserirNaFila(f3, 'B');
    inserirNaFila(f3, 'D');
    inserirNaFila(f3, 'J');

    Fila *f4;
    f4 = criarFila();

    inserirNaFila(f4, 'G');
    inserirNaFila(f4, 'U');
    inserirNaFila(f4, 'B');
    inserirNaFila(f4, 'D');
    inserirNaFila(f4, 'J');

    Fila *f5;
    f5 = criarFila();

    inserirNaFila(f5, 'g');
    inserirNaFila(f5, 'u');
    inserirNaFila(f5, 'b');
    inserirNaFila(f5, 'd');
    inserirNaFila(f5, 'j');

    printf("['G','U','B','D','J'] == ['G','U','B','D','J'] ? %s\n", verificarFilasIguais(f3, f4) == 1 ? "VERDADEIRO" : "FALSO");
    printf("['G','U','B','D','J'] == ['g','u','b','d','j'] ? %s", verificarFilasIguais(f3, f5) == 1 ? "VERDADEIRO" : "FALSO");

    liberarFila(f2);
    liberarFila(f3);
    liberarFila(f4);
    liberarFila(f5);

    return 0;
}