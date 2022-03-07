#include <stdio.h>
#include <stdlib.h>
//#include "lista.h"
#include "TadLista.c"

int main() {
    Lista *carrinhoCompras = criar();
    int ok;
    inserir(carrinhoCompras, 'J', &ok);
    inserir(carrinhoCompras, 'P', &ok);
    inserir(carrinhoCompras, 'A', &ok);
    inserir(carrinhoCompras, 'D', &ok);

    Lista *listaCompras = criar();
    inserir(listaCompras, 'P', &ok);
    inserir(listaCompras, 'A', &ok);
    inserir(listaCompras, 'A', &ok);
    inserir(listaCompras, 'Q', &ok);

    printf("Carrinho de compras: \n");
    imprimir(carrinhoCompras);
    printf("\nLista de compras:\n");
    imprimir(listaCompras);

    Elemento *primeiro;
    pegaOPrimeiro(carrinhoCompras, &primeiro);

    printf("\nPrimeiro elemento do carrinho: %c ", primeiro->conteudo);

    printf("\nQuantidade itens errados: %d", itensCompradosErroneamente(carrinhoCompras, listaCompras));


    //printf("Quantidade comprada errada: %d", itensCompradosErroneamente(carrinhoCompras, listaCompras));
}