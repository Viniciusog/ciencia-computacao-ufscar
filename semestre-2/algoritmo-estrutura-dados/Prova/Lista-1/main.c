
#include <stdio.h>
#include <stdlib.h>
#include "./lista.h"

int main() {
    NodePtr *l;
    l = criar();
    inserir(l, 12);
    inserir(l, 14);
    inserir(l, 14);
    inserir(l, 14);
    inserir(l, 14);
    inserir(l, 14);
    inserir(l, 14);
    inserir(l, 14);
    inserir(l, 17);
    inserir(l, 17);
    inserir(l, 17);
    inserir(l, 17);
    imprimir(l);
    printf("\n");
    int ok;
    Remove1(l, 14, &ok);
    RemoveTodos(l, 17, &ok);
    imprimir(l);
}