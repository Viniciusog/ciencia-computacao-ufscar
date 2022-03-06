#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct node {
    int conteudo;
    Node *proximo;
} Node;

typedef struct fila {
    Node *inicio;
    int tam;
} Fila;

Node *criarNode(int valor) {
    Node *novo = malloc(sizeof(Node));
    novo->conteudo = valor;
    return novo;
}

Fila *criar() {
    Fila *fila = malloc(sizeof(Fila));
    fila->tam = 0;
    return fila;
}

void inserir(Fila *fila, int idade) {
    Node *novo = criarNode(idade);
    // Se a fila tiver vazia
    if (fila->tam == 0) {
        novo->proximo = novo;
        fila->inicio = novo;
    } 
    // Se a fila tiver 1 elemento
    else if (fila->tam == 1) {
        // Se o primeiro elemento tiver conteúdo maior ou igual 
        // ao do novo, então iremos apenas adicionar o novo no final da fila.
        if (fila->inicio->conteudo >= novo->conteudo) {
            fila->inicio->proximo = novo;
            novo->proximo = fila->inicio;
        } else {
            novo->proximo = fila->inicio;
            fila->inicio->proximo = novo;
            fila->inicio = novo;
        }
    } 
    // Se a fila tiver 2 ou mais elementos
    else {
        Node *atual = fila->inicio;
        // novo = [78]
        // [inicio = 89] -> [85] -> [81] -> [75] -> inicio
        // [inicio = 89] -> [85] -> [81] -> [78]-> [75] -> inicio

        // novo = [73]
        // [inicio = 89] -> [85] -> [81] -> [75] -> inicio
        // [inicio = 89] -> [85] -> [81] -> [75] -> [73] -> inicio
        while (atual->proximo->conteudo >= novo->conteudo && atual->proximo != fila->inicio) {
            atual = atual->proximo;
        } 
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
    (fila->tam)++;
}

int remover(Fila *fila) {
    if (fila->tam == 0) return NULL;

    Node *paraRemover = fila->inicio;
    int valor = paraRemover->conteudo;

    // Se a fila tiver apenas 1 elemento
    if (fila->tam == 1) {
        fila->inicio = NULL;
    } else {
        fila->inicio = paraRemover->proximo;
        // Vamos percorrer toda a lista para encontrar o último elemento e 
        // em seguida, colocar o 'próximo' do último elemento apontando para o 
        // 'novo' inicio da fila.
        Node *atual = fila->inicio;
        // [paraRemover] -> [novo inicio] -> [76] -> [54] -> [32] -> [paraRemover]
        // ficará
        // [paraRemover] -> [novo inicio] -> [76] -> [54] -> [32] -> [novo inicio]
        while (atual->proximo != paraRemover) {
            atual = atual->proximo;
        }
        // "atual" é o último elemento. E apontará para o novo início da fila.
        atual->proximo = fila->inicio; 
    }
    free(paraRemover);
    (fila->tam)--;
    return valor;
}

// [inicio = 87] -> [67] -> [inicio]
void imprimir(Fila *fila) {
    Node *atual = fila->inicio;
    for (int i = 0; i < fila->tam; i++) {
        printf("%d ", atual->conteudo);
        atual = atual->proximo;
    }
}