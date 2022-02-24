#include <stdio.h>
#include <stdlib.h>
#include "listaCadastral.h"

int main() {

    Node * cabeca;
    cabeca = criar();

    inserir(cabeca, 'G');
    inserir(cabeca, 'F');
    inserir(cabeca, 'O');
    inserir(cabeca, 'K');
    inserir(cabeca, 'F');
    inserir(cabeca, 'E');
    inserir(cabeca, 'A');
    inserir(cabeca, 'T');

    imprimir(cabeca);

    remover(cabeca, 'F');

    printf("\nAo remover 'F': ");
    imprimir(cabeca);

    printf("\nA lista é vazia? %s", vazia(cabeca) ? "SIM" : "NÃO");

    Node *cabeca2;
    cabeca2 = copiar(cabeca);

    printf("\n\nLista1: G, F, O, K, E, A, T");
    printf("\nLista2: G, F, O, K, E, A, T");
    printf("\nSão iguais? %s", saoIguais(cabeca, cabeca2) == 1 ? "SIM" : "NÃO");

    inserir(cabeca2, 'Y');

    printf("\n");
    printf("\nLista1: G, F, O, K, E, A, T");
    printf("\nLista2: G, F, O, K, E, A, T, Y");
    printf("\nSão iguais? %s", saoIguais(cabeca, cabeca2) == 1 ? "SIM" : "NÃO");


    Node * cabecaA;
    cabecaA = criar();

    inserir(cabecaA, 'H');
    inserir(cabecaA, 'I');
    inserir(cabecaA, 'O');
    inserir(cabecaA, 'A');

    Node * cabecaB;
    cabecaB = criar();

    inserir(cabecaB, 'I');
    inserir(cabecaB, 'K');
    inserir(cabecaB, 'A');
    inserir(cabecaB, 'J');

    printf("\n\nLista A: ");
    imprimir(cabecaA);
    printf("\nLista B: ");
    imprimir(cabecaB);

    printf("\nIntersecção das listas A com B: ");
    imprimir(interseccao(cabecaA, cabecaB));

    printf("\nJunção das listas A com B: ");
    Node *cabecaJuncao = juntarListas(cabecaA, cabecaB);
    imprimir(cabecaJuncao);    
    printf("\nTamanho da lista da junção: %d", tamanho(cabecaJuncao));
    
    printf("\n'P' está na lista da junção? %s", estaNaLista(cabecaJuncao, 'P') == 1 ? "SIM" : "NÃO");
}