
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct nodePtr {
    NodePtr *next;
    int info;
} NodePtr;

NodePtr *criar() {
    NodePtr *l = malloc(sizeof(NodePtr));
    l->next = NULL;
    l->info = 0;
    return l;
}

void inserir(NodePtr *l, int x) {
    NodePtr *p = criar();
    p->info = x;
    p->next = l->next;
    l->next = p;
}

void imprimir(NodePtr *l) {
    NodePtr *p = l->next;
    while (p != NULL) {
        printf("%d ", p->info);
        p = p->next;
    }
}

// Remove a primeira ocorrência de um determinado valor
void Remove1(NodePtr *l, int x, int *ok) {
    NodePtr *p = l->next;
    
    // Se a lista está vazia
    if (p == NULL){
        *ok = 0;
    }
    // Se o primeiro valor da lista for para ser removido;
    else if (p->info == x) {
        l->next = p->next;
        free(p);
        *ok = 1;
    } else {
        while (p->next != NULL && p->next->info != x) {
            p = p->next;
        }
        // Se foi encontrado elemento com valor igual na lista
        if (p->next != NULL) {
            NodePtr *toRemove = p->next;
            p->next = toRemove->next;
            free(toRemove);
            *ok = 1; 
        } else {
            *ok = 0;
        }
    }
}

// Remove todas as ocorrências de um determinado valor
void RemoveTodos(NodePtr *l, int x, int *ok) {
    NodePtr *p = l->next;

    // Se removeu pelo menos uma vez
    int removeu1 = 0;
    // Situação da última tentativa de remover
    int okRemove1 = 1;

    //Enquanto tiver elemento para remover
    while (okRemove1) {
        Remove1(l, x, &okRemove1);
        // Se removeu pelo menos uma vez
        if (okRemove1 == 1 && removeu1 == 0) {
            removeu1 = 1;
        }
    }
    *ok = removeu1;
}
