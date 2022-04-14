
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct elemento {
    int conteudo;
    Elemento *proximo;
} Elemento;

typedef struct lista {
    Elemento *inicio;
    Elemento *atual;
    int tam;
} Lista;

Lista *criar() {
    Lista * lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->atual = NULL;
    lista->tam = 0;
}

void inserir(Lista *lista, char valor, int *ok) {
    Elemento *novo = malloc(sizeof(Elemento));
    novo->conteudo = valor;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    (lista->tam)++;
    *ok = 1;
}

int vazia(Lista *lista) {
    return lista->tam == 0 ? 1 : 0;
}

void remover(Lista *lista, char valor, int *ok) {
    if (vazia(lista)) {
        *ok = 0;
        return;
    }

    Elemento *atual = lista->inicio;

    // Se a lista tiver apenas um elemento
    if (lista->tam == 1) {
        if (atual->conteudo == valor) {
            free(atual);
            *ok = 1;
            (lista->tam)--;
        } else {
            *ok = 0;
        }
    } else {
        //Encontrar o primeiro elemento com conteúdo igual ao do valor. 
        //O elemento encontrado será: atual->proximo.
        while (atual->proximo != NULL && atual->proximo->conteudo != valor) {
            atual = atual->proximo;
        }   

        // Se não existir o elemento com o determinado valor dentro da lista
        if (atual->proximo == NULL) {
            *ok = 0;
        } else {
            Elemento *paraRemover = atual->proximo;
            atual->proximo = paraRemover->proximo;
            free(paraRemover);
            *ok = 1;
            (lista->tam)--;
        }
    }
} 

void imprimir(Lista *lista) {
    Elemento *atual = lista->inicio;
    while (atual != NULL) {
        printf("%c ", atual->conteudo);
        atual = atual->proximo;
    }
}


int estaNaLista(Lista *lista, char valor) {
    Elemento *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->conteudo == valor) {
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void pegaOPrimeiro(Lista *lista, Elemento **elemento) {
    *elemento = lista->inicio;
    lista->atual = lista->inicio;
}

void pegaOProximo(Lista *lista, Elemento **elemento, int *temElemento) {
    *elemento = lista->atual->proximo;
    lista->atual = lista->atual->proximo;
    //Caso a lista estiver vazia
    if (*elemento == NULL) {
        *temElemento = 0;
    } else {
        *temElemento = 1;
    }
}

int itensCompradosErroneamente(Lista *carrinhoCompras, Lista *listaCompras) {
    Elemento *atual;
    pegaOPrimeiro(carrinhoCompras, &atual);
    int qtdErrada = 0;
    int temElemento;

    while (atual != NULL) {
        if (!estaNaLista(listaCompras, atual->conteudo)) {
            qtdErrada++;
        }
        pegaOProximo(carrinhoCompras, &atual, &temElemento);
    }
    return qtdErrada;
}