#include <stdlib.h>
#include <stdio.h>
#include "./pilha.h"

typedef struct elemento {
    char info;
    Elemento *dir;
    Elemento *esq;
} Elemento;

typedef struct pilha {
     Elemento *dir;
} Pilha;

Pilha *criar() {
    Pilha *header = malloc(sizeof(Pilha));
    header->dir = NULL;
    return header;
}

Elemento *criarElemento(char x) {
    Elemento *e = malloc(sizeof(Elemento));
    e->info = x;
    return e;
}

void empilha(Pilha *header, Elemento *x) {
    //Se a pilha estiver vazia
    if (header->dir == NULL) {
        header->dir = x;
        x->dir = header->dir;
        x->esq = header->dir;
    } 
    // Se a lista tiver 1 elemento
    else if (header->dir->dir == header->dir) {
        x->dir = header->dir;
        x->esq = header->dir;
        header->dir->dir = x;
        header->dir->esq = x;
        header->dir = x;
    }
    //Se tiver 2 ou mais elementos dentro da pilha
    else {
        //Pega o último elemento da pilha -> O(n)
        Elemento *atual = header->dir;
        while (atual->dir != header->dir) {
            atual = atual->dir;
        }
        //x->dir = primeiro da pilha
        x->dir = header->dir; 
        //x->esq = último da pilha
        x->esq = atual;
        //o último elemento irá apontar para o X
        atual->dir = x;
        //primeiro da pilha irá apontar (esq) para X
        header->dir->esq = x;
        //X é o novo primeiro da pilha
        header->dir = x;
    }
}

void desempilha(Pilha *header) {
    if (header->dir == NULL) {
        printf("Pilha vazia!");
    } 
    //Se tiver apenas 1 elemento na pilha
    else if (header->dir->dir == header->dir) {
        Elemento *paraRemover = header->dir;
        free(paraRemover);
        header->dir = NULL;
    }
    //Se tiver mais de um elemento dentro da pilha
    else {
        //Pega o último elemento da pilha
        Elemento *atual = header->dir;
        while (atual->dir != header->dir) {
            atual = atual->dir;
        }
        //Remove primeiro elemento da pilha
        Elemento *paraRemover = header->dir;
        header->dir = paraRemover->dir;
        header->dir->esq = atual;
        atual->dir = header->dir;
        free(paraRemover);
    }
} 

int vazia(Pilha *header) {
    return header->dir == NULL ? 1 : 0;
}