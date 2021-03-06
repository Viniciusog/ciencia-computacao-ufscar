#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

int main() {
    Node *cabeca = criarLista();
    inserir(cabeca, 'T');
    inserir(cabeca, 'Y');
    inserir(cabeca, 'A');
    inserir(cabeca, 'Y');
    inserir(cabeca, 'D');

    imprimir(cabeca); // D Y A Y Tsdfgdfg
    buscaRemove(cabeca, 'Y');
    printf("\n");
    
    imprimir(cabeca); // D A Y Tdfgfdg
    printf("\n");

    buscaInsere(cabeca, 'A', 'M'); 
    imprimir(cabeca); // D M A Y T
}