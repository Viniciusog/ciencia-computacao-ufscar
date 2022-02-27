#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct node {
    char conteudo;
    Node *proximo;
} Node;

Node *criarLista() {
    Node *cabeca;
    cabeca = (Node *) malloc(sizeof(Node));
    cabeca->proximo = NULL;
    return cabeca;
}

Node *criarNode(char valor) {
    Node *node;
    node = (Node *) malloc(sizeof(Node));
    node->conteudo = valor;
}

void inserir(Node *cabeca, char valor) {
    Node *novo;
    novo = (Node *) malloc(sizeof(Node));
    novo->conteudo = valor;

    // Se a lista estiver vazia
    if (cabeca->proximo == NULL) {
        novo->proximo = cabeca; 
    } else {
        novo->proximo = cabeca->proximo;
    }
    cabeca->proximo = novo;
}

// [  ] -> null
// [  ] -> [] -> []
// Remove o primeiro elemento da lista
char remover(Node *cabeca) {
    if (cabeca->proximo == NULL) return '\0';

    Node *paraRemover = cabeca->proximo;
    char valor = paraRemover->conteudo;

    // Se tiver apenas um elemento na lista
    // A cabeça apontará para null quando ele for removido ao invés 
    // de apontar para si própria caso pegasse paraRemover->proximo
    if (paraRemover->proximo == cabeca) {
        cabeca->proximo = NULL;
    } else {
        cabeca->proximo = paraRemover->proximo;
    }
    free(paraRemover);
    return valor;
}

void imprimir(Node *cabeca) {
    Node *atual;
    atual = cabeca->proximo;
    //Percorre a lista apenas uma vez, sem voltar para o início.
    while (atual != cabeca) {
        char valor = atual->conteudo;

        printf("%c ", valor);
        atual = atual->proximo;
    }
}

// Encontra o primeiro elemento com um determinado valor e retorna um ponteiro para ele.
// Se o valor não existir dentro da lista, então o ponteiro retornado apontará para a cabeça.
Node *buscar(Node *cabeca, char valor) {
    Node *atual = cabeca->proximo;

    // [ CABEÇA ] -> [] -> [] -> [ CABEÇA ]
    while (atual != cabeca && atual->conteudo != valor) {
        atual = atual->proximo;
    }
    return atual;
}

//Retorna um ponteiro para o elemento que está em uma posição da lista.
//Se a lista tiver um único elemento, então retornaremos o ponteiro da cabeça.
Node *selecionar(Node *cabeca, int posicao) {
    Node *atual = cabeca->proximo;
    int index = 0;

    while (atual != cabeca && index < posicao) {
        atual = atual->proximo;
        index++;
    }
    return atual;
}

// Encontra o primeiro elemento com determinado valor e insere o segundo valor antes dele.
void buscaInsere(Node *cabeca, char valor1, char valor2) {
    Node *atual = cabeca->proximo;

    // [  ] -> null;
    // Se a lista estiver vazia
    if (atual == NULL) {   
        Node *novo = criarNode(valor2);
        novo->proximo = cabeca;
        cabeca->proximo = novo;
    }

    // [  ] -> [] -> [] -> [] -> [] -> [  ]
    while (atual->proximo != cabeca && atual->proximo->conteudo != valor1) {
        atual = atual->proximo;
    }

    // Se chegou aqui, então o atual->proximo->conteudo == valor1 ou atual->proximo == cabeca
    Node *novo = criarNode(valor2);
    novo->proximo = atual->proximo;
    atual->proximo = novo;


    /* if (atual->proximo->conteudo == valor1) {
        Node *novo = criarNode(valor2);
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }  */

    // Se não existir elemento com o determinado valor dento da lista
    /* else if (atual->proximo == cabeca) {
        Node *novo = criarNode(valor2);
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    } */
}

//Remove o primeiro elemento encontrado com determinado valor
void buscaRemove(Node *cabeca, char valor) {
    Node *atual = cabeca->proximo;

    // Se a lista estiver vazia
    if (atual == NULL) {
        return;
    }

    // Se a lista tiver apenas 1 elemento
    if (atual->proximo == cabeca) {
        Node *paraRemover = atual;
        cabeca->proximo = NULL;
        free(paraRemover);
        return;
    }

    // Se for para remover o primeiro elemento da lista
    if (atual->conteudo == valor) {
        Node *paraRemover = atual;
        cabeca->proximo = paraRemover->proximo;
        free(paraRemover);
        return;
    }

    // Se o elemento para remover estiver no meio da lista
    //[  ] -> [] -> [] -> [] -> [  ]
    while (atual->proximo != cabeca && atual->proximo->conteudo != valor) {
        atual = atual->proximo;
    }

    // Só iremos remover o item da lista caso tiver o elemento dentro da lista.
    if (atual->proximo != cabeca) {
        Node *paraRemover = atual->proximo;
        atual->proximo = paraRemover->proximo;
        free(paraRemover);
    }
}