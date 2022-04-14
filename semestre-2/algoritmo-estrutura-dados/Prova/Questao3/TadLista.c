
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct pessoa {
    int info;
    Pessoa *next;
} Pessoa;

typedef struct lista {
    // Primeira pessoa da lista
    Pessoa *next;
    // Controla qual foi a última pessoa a ser chamada
    Pessoa *atual;
} Lista;    


Lista *criar() {
    Lista * lista = malloc(sizeof(Lista));
    lista->next = NULL;
    lista->atual = NULL;
}

void insere(Lista *lista, int valor, int *ok) {
    Pessoa *p = malloc(sizeof(Pessoa));
    p->info = valor;
    p->next = lista->next;
    lista->next = p;
    *ok = 1;
}

int vazia(Lista *lista) {
    return lista->next == NULL ? 1 : 0;
}

void remover(Lista *lista, int valor, int *ok) {
    if (vazia(lista)) {
        *ok = 0;
        return;
    }

    Pessoa *atual = lista->next;
    // Se tiver apenas um elemento na lista
    if (lista->next->next == NULL) {
        if (atual->info == valor) {
            lista->next = atual->next;
            free(atual);
        } else {
            *ok = 0;
        }
    } 
    // Se tiver mais do que um elemento dentro da lista
    else {
        // Se logo o primeiro elemento tiver valor igual
        if (atual->info == valor) {
            lista->next = atual->next;
            free(atual);
        } else {
            while (atual->next != NULL && atual->next->info != valor) {
                atual = atual->next;
            }
            // Se tiver encontrado o valor dentro da lista
            if (atual->next->info == valor) {
                Pessoa *paraRemover = atual->next;
                atual->next = paraRemover->next;
                free(paraRemover);
                *ok = 1;
            } else {
                *ok = 0;
            }
        }
    }
} 

void imprimir(Lista *lista) {
    Pessoa *atual = lista->next;
    while (atual != NULL) {
        printf("%d ", atual->info);
        atual = atual->next;
    }
}


int estaNaLista(Lista *lista, int valor) {
    Pessoa *atual = lista->next;
    while (atual != NULL) {
        if (atual->info == valor) {
            return 1;
        }
        atual = atual->next;
    }
    return 0;
}

void pegaOPrimeiro(Lista *lista, Pessoa **pessoa) {
    *pessoa = lista->next;
    lista->atual = lista->next;
}

void pegaOProximo(Lista *lista, Pessoa **pessoa, int *temElemento) {
    *pessoa = lista->atual->next;
    lista->atual = lista->atual->next;
    //Caso a lista estiver vazia
    if (*pessoa == NULL) {
        *temElemento = 0;
    } else {
        *temElemento = 1;
    }
}

int nroPessoasVacinadasOuInfectadas(Lista *l1, Lista *l2) {
    int qtd1 = 0;

    Pessoa *atual1;
    pegaOPrimeiro(l1, &atual1);
    int temElemento;

    while (atual1 != NULL) {
        qtd1++;
        pegaOProximo(l1, &atual1, &temElemento);
    }

    Pessoa *atual2;
    pegaOPrimeiro(l2, &atual2);
    while (atual2 != NULL) {
        if (estaNaLista(l1, atual2->info) == 0) {
            qtd1++;
        }
        pegaOProximo(l2, &atual2, &temElemento);
    }

    return qtd1;
}