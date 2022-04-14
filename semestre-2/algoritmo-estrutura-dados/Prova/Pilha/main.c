#include <stdio.h>
#include <stdlib.h>
#include "./pilha.h"

int main() {
    Pilha *header = criar();

    Elemento *a = criarElemento('A');
    Elemento *b = criarElemento('B');
    Elemento *c = criarElemento('C');

    empilha(header, a);
    empilha(header, b);
    empilha(header, c);
    
    printf("Vazia? %s", vazia(header) == 1 ? "sim" : "não");

    Pilha *header2 = criar();
    printf("\nVazia? %s", vazia(header2) == 1 ? "sim" : "não");
}