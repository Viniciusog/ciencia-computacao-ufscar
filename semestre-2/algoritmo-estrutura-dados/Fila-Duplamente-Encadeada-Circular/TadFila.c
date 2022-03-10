
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct node {
    char conteudo;
    Node *proximo;
    Node *anterior;
} Node;

typedef struct fila {
    Node *inicio;
    Node *fim;
    int tam;
} Fila;

Fila *criar() {
    Fila *fila = malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tam = 0;
    return fila;
}

void inserir(Fila *fila, char valor) {

    Node *novo = malloc(sizeof(Node));
    novo->conteudo = valor;

    // Se a fila estiver vazia
    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
        fila->inicio->proximo = fila->fim;
        fila->inicio->anterior = fila->fim;
        fila->fim->proximo = fila->inicio;
        fila->fim->anterior = fila->inicio;
    } else {
        fila->fim->proximo = novo;
        fila->fim->proximo->anterior = fila->fim;
        fila->fim = novo;
        fila->fim->proximo = fila->inicio;
        fila->inicio->anterior = fila->fim; 
    } 
    (fila->tam)++;
}

char remover(Fila *fila) {
    // Se a fila for vazia
    if (fila->tam == 0) return '\0';
    
    Node *paraRemover = fila->inicio;
    char valor = paraRemover->conteudo;
    
    // Se tiver apenas um elemento dentro da fila
    if (fila->tam == 1) {
        fila->inicio = NULL;
        fila->fim = NULL;
    } else {
        fila->inicio = paraRemover->proximo;
        fila->inicio->anterior = fila->fim;
        fila->fim->proximo = fila->inicio;
    }
    free(paraRemover);
    (fila->tam)--;
    return valor;
}

int vazia(Fila *fila) {
    return fila->inicio == NULL ? 1 : 0;
}

void imprimir(Fila *fila) {
    Node *atual = fila->inicio;
    for (int i = 0; i < fila->tam; i++) {
        printf("%c ", atual->conteudo);
        atual = atual->proximo;
    }
}

void destruir(Fila *fila) {
    Node *atual = fila->inicio;
    //Se a fila tiver nenhum elemento, não executará o for, pois i é igual a 0 (igual ao tamanho)
    //Se a fila tiver apenas um elemento, o for executará uma vez, pois i será 0 (menor que 1)
    //Se a fila tiver dois elementos, o for executará duas vezes, pois i será 0 e 1 (menor que o tammanho 2)
    for (int i = 0; i < fila->tam; i++) {
        free(atual);
        atual = atual->proximo;
    }
    free(fila);
}
