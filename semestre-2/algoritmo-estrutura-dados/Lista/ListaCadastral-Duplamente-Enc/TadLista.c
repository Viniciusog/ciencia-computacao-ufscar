#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct node {
    char conteudo;
    Node *proximo;
    Node *anterior;
} Node;

Node *criar() {
    Node *cabeca = malloc(sizeof(Node));
    cabeca->proximo = NULL;
    return cabeca;
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

// Remove o primeiro elemento encontrado com determinado valor
void remover(Node *cabeca, char valor) {
    Node *atual = cabeca->proximo;

    // [  ] -> [] -> [] -> [] -> null
    while (atual->conteudo != valor && atual != NULL) {
        atual = atual->proximo;
    }

    // Se existir o elemento dentro da lista
    if (atual != NULL) {
        // Se for o último elemento da lista
        if (atual->proximo == NULL) {
            Node *paraRemover = atual;
            paraRemover->anterior->proximo = paraRemover->proximo;
            free(paraRemover);
        } 
        // Se o elemento para remover estiver entre elementos
        else {
            Node *paraRemover = atual;
            paraRemover->anterior->proximo = paraRemover->proximo;
            paraRemover->proximo->anterior = paraRemover->anterior;
            free(paraRemover);
        }
    }
}

void imprimir(Node *cabeca) {
    Node *atual = cabeca->proximo;
    while (atual != NULL) {
        printf("%c ", atual->conteudo);
        atual = atual->proximo;
    }
}

//Retorna o valor do elemento que corresponde ao elemento com maior valor ASCII
char maiorValorASCII(Node *cabeca) {
    Node *atual = cabeca->proximo;

    char maiorValor = atual->conteudo;

    while (atual != NULL) {
        if (atual->conteudo > maiorValor) {
            maiorValor = atual->conteudo;
        }
        atual = atual->proximo;
    }

    return maiorValor;
}

//Insere um elemento com valor2 antes do primeiro elemento que o conteúdo é igual a valor1
void buscaInserir(Node *cabeca, char valor1, char valor2) {
    Node *atual = cabeca->proximo;

    Node *novo = malloc(sizeof(Node));
    novo->conteudo = valor2;

    Node *elAnterior;

    while (atual != NULL && atual->conteudo != valor1) {
        // Se não tivermos mais elementos na lista
        if (atual->proximo == NULL) {
            // [  ] ⇆ [] ⇆ [] ⇆ [atual] -> null
            elAnterior = atual;
        }
        atual = atual->proximo;
    }

    // Se não tem elemento na lista com conteúdo igual ao valor2, então
    // iremos adicionar o elemento no final da lista
    if (atual == NULL) {
        // [  ] ⇆ [] ⇆ [] ⇆ [elAnterior] -> null
        // [  ] ⇆ [] ⇆ [] ⇆ [elAnterior] ⇆ [novo] -> null
        novo->proximo = NULL;
        novo->anterior = elAnterior;
        elAnterior->proximo = novo;
    } 
    // Se temos elemento na lista
    else {
        // [  ] ⇆ [] ⇆ [atual] ⇆ [] -> null
        // [  ] ⇆ [] ⇆ [novo] ⇆ [atual] ⇆ [] -> null
        novo->proximo = atual;
        novo->anterior = atual->anterior;
        atual->anterior->proximo = novo;
        atual->anterior = novo;
    }
}
