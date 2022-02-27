#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

typedef struct node {
    char conteudo;
    Node *proximo;
    Node *anterior;
} Node;

Node * criar() {
    Node *cabeca = (Node *) malloc(sizeof(Node));
    cabeca->proximo = NULL;
    return cabeca;
}

int vazia(Node *cabeca) {
    return cabeca->proximo == NULL ? 1 : 0;
}

void inserir(Node *cabeca, char valor) {
    Node *novo;
    novo = (Node *) malloc(sizeof(Node));
    novo->conteudo = valor;

    // Se a lista for vazia
    if (cabeca->proximo == NULL) {
        novo->proximo = cabeca->proximo;
        novo->anterior = cabeca;
        cabeca->proximo = novo;
    } 
    // Se já tiver elementos dentro da lista
    else {
        novo->proximo = cabeca->proximo;
        novo->anterior = cabeca;
        cabeca->proximo->anterior = novo;
        cabeca->proximo = novo;
    }
}

char remover(Node *cabeca) {
    if (cabeca->proximo == NULL) {
        return '\0';
    }
    
    Node *paraRemover = cabeca->proximo;
    char valor = paraRemover->conteudo;

    // Se tiver apenas um elemento na lista
    if (paraRemover->proximo == NULL) {
        cabeca->proximo = paraRemover->proximo;
    } 
    // Se tiver mais de um elemento na lista
    else {
        paraRemover->proximo->anterior = cabeca;
        cabeca->proximo = paraRemover->proximo;
    }

    free(paraRemover);
    return valor;
}

void imprimir(Node *cabeca) {
    Node *atual = cabeca->proximo;
    // [Cabeça] ⇆ [] ⇆ [atual] ⇆ [] → null

    while (atual != NULL) {
        printf("%c ", atual->conteudo);
        atual = atual->proximo;
    }
}

//Busca elemento na lista e adiciona item antes desse elemento
void buscaInsere(Node *cabeca, char valor1, char valor2) {
    // ⇆ é dupla ligação
    // → é ligação simples para o próximo

    Node *atual = cabeca->proximo;
    
    Node *novo = malloc(sizeof(Node));
    novo->conteudo = valor2;

    // Elemento anterior, representa o anterior ao NULL
    Node *elAnterior = malloc(sizeof(Node));

    // [  ] ⇆ [] ⇆ [] ⇆ [] → null
    while (atual->conteudo != valor1 && atual != NULL) {
        if (atual->proximo == NULL) {
            elAnterior = atual;
        }
        atual = atual->proximo;
    }

    // Se for inserir elemento entre dois elementos
    if (atual->conteudo == valor1) {
        // [Cabeça] ⇆ [] ⇆ [atual] ⇆ [] → null
        // [Cabeça] ⇆ [] ⇆ [novo] ⇆ [atual] ⇆ [] → null
        novo->proximo = atual;
        novo->anterior = atual->anterior;
        atual->anterior->proximo = novo;
        atual->anterior = novo;
    } 
    // Atual aqui será NULL
    // Iremos inserir o valor no final da lista
    else {
        // [Cabeça] ⇆ [elAnterior] → null
        // [Cabeça] ⇆ [elAnterior] ⇆ [novo] → null
        novo->proximo = NULL;
        novo->anterior = elAnterior;
        elAnterior->proximo = novo;
    }
}

//Remove o primeiro elemento encontrado com determinado valor
void buscaRemove(Node *cabeca, char valor) {
    Node *atual = cabeca->proximo;

    // [Cabeça] ⇆ [] ⇆ [] → null
    while (atual->conteudo != valor && atual != NULL) {
        atual = atual->proximo;
    }

    // Só podemos remover um elemento se ele for diferente de NULL
    if (atual != NULL) {
    
        // Se for para remover o último elemento 
        // [Cabeça] ⇆ [] ⇆ [paraRemover] → null
        if (atual->proximo == NULL) {
            Node *paraRemover = atual;
            paraRemover->anterior->proximo = NULL;
            free(paraRemover);
        } 
        // Se for para remover entre elementos      
        // [Cabeça] ⇆ [paraRemover] ⇆ [] → null  
        else {
            Node *paraRemover = atual;
            paraRemover->anterior->proximo = paraRemover->proximo;
            paraRemover->proximo->anterior = paraRemover->anterior;
            free(paraRemover);
        }
    }
}

