#include <stdio.h>
#include <stdlib.h>
#include "listaCadastral.h"


typedef struct node {
    char conteudo;
    Node * proximo;
} Node;

// ** FUNÇÕES PRIMITIVAS ** //

Node * criar() {
    Node * cabeca;
    cabeca = (Node *) malloc(sizeof(Node));
    cabeca->proximo = NULL;
    return cabeca;
}

Node * inserir(Node * cabeca, char valor) {
    Node * novo;
    novo = (Node *) malloc(sizeof(Node));
    novo->conteudo = valor;
    novo->proximo = cabeca->proximo;

    cabeca->proximo = novo;
    return novo;
}

// Remove o primeiro elemento que contém um determinado valor
char remover(Node * cabeca, char valor) {
    // null <- [G] <- [A] <- [K] <- [Cabeça]
    if (vazia(cabeca)) {
        return '\0';
    }

    Node * atual;
    atual = cabeca->proximo;

    // Se o primeiro elemento tiver conteúdo igual ao valor.
    if (atual->conteudo == valor) {
        cabeca->proximo = atual->proximo;
        char conteudo = atual->conteudo;
        free(atual);
        return conteudo;
    }

    // Caso o elemento esteja no meio da lista.
    while (atual != NULL && atual->proximo != NULL) {
        if (atual->proximo->conteudo == valor) {
            Node *paraRemover = atual->proximo;
            char conteudo = paraRemover->conteudo;
            atual->proximo = paraRemover->proximo;
            free(paraRemover);
            return conteudo;
        }
        atual = atual->proximo;
    }
    // Se não tiver elemento na lista com o conteúdo sendo o valor.
    return '\0';
}

int vazia(Node * cabeca) {
    return cabeca->proximo == NULL ? 1 : 0;
}

// ** FUNÇÕES NÃO PRIMITIVAS ** //

// Remove todos os elementos da lista cadastral
void destruir(Node * cabeca) {
    Node * atual;
    atual = cabeca->proximo;

    while (atual != NULL) {
        Node * paraRemover = atual;
        cabeca->proximo = paraRemover->proximo;
        free(paraRemover);
        atual = cabeca->proximo;
    }
    free(cabeca);
}

// Retorna uma outra lista como sendo uma cópia da lista passada por parâmetro
Node * copiar(Node * cabeca) {
    Node * cabecaAux;
    cabecaAux = criar();

    Node * cabecaRes;
    cabecaRes = criar();

    Node * atual;
    atual = cabeca->proximo;

    // G, U, A, R, U, Cabeca;
    // U, R, A, U, G, CabecaAux;
    while (atual != NULL) {
        char valor = atual->conteudo;
        inserir(cabecaAux, valor);
        atual = atual->proximo;
    }

    atual = cabecaAux->proximo;
    // U, R, A, U, G, CabecaAux;
    // G, U, A, R, U, CabecaRes;
    while (atual != NULL) {
        char valor = atual->conteudo;
        inserir(cabecaRes, valor);
        atual = atual->proximo;
    }
    destruir(cabecaAux); 

    return cabecaRes;
}

//1: Está na lista, 0: Não está na lista
int estaNaLista(Node *cabeca, char valor) {
    Node * atual;
    atual = cabeca->proximo;

    while(atual != NULL) {
        if (atual->conteudo == valor) {
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}


// Junta os elementos de duas listas.
// Precisamos de uma lista auxiliar para que os itens fiquem na ordem
// correta na parte de inserir na lista resultante
/*
K, I, T, A lista principal
A, T, I, K lista auxiliar (Pega itens da lista principal)
K, I, T, A lista resultante (Pega itens da lista auxiliar)
*/
Node * juntarListas(Node * cabeca1, Node * cabeca2) {
    Node *cabecaRes = copiar(cabeca1);
    
    Node *cabecaAux;
    cabecaAux = criar();
    
    Node *atual;
    atual = cabeca2->proximo;
    
    while (atual != NULL) {
        char valor = atual->conteudo;
        inserir(cabecaAux, valor);
        atual = atual->proximo;
    }
    
    atual = cabecaAux->proximo;
    while (atual != NULL) {
        char valor = atual->conteudo;
        inserir(cabecaRes, valor);
        atual = atual->proximo;
    }
    
    return cabecaRes;
}

// Considera apenas os elementos válidos (Não cabeça e não null).
int tamanho(Node * cabeca) {
    Node * atual;
    atual = cabeca->proximo;

    int qtd = 0;

    while (atual != NULL) {
        qtd++;
        atual = atual->proximo;    
    }

    return qtd;
}

void imprimir(Node *cabeca) {
    Node * atual;
    atual = cabeca->proximo;

    Node * cabecaAux;
    cabecaAux = criar();

    while (atual != NULL) {
        char valor = atual->conteudo;
        inserir(cabecaAux, valor);
        atual = atual->proximo;
    }

    atual = cabecaAux->proximo;

    while (atual != NULL) {
        char valor = atual->conteudo;
        printf("%c ", valor);
        atual = atual->proximo;
    }

    destruir(cabecaAux);
}

// Percorre os elementos da menor lista e verifica se estão na lista maior.
// Se estiverem, então adiciona em uma lista resultante
Node * interseccao(Node *cabeca1, Node *cabeca2) {
    int tamanho1 = tamanho(cabeca1);
    int tamanho2 = tamanho(cabeca2);

    Node * atual;
    atual = tamanho1 >= tamanho2 ? cabeca2->proximo : cabeca1->proximo;

    Node * cabecaRes;
    cabecaRes = criar();

    while (atual != NULL) {
        char valor = atual->conteudo;
        if (estaNaLista(tamanho1 >= tamanho2 ? cabeca1 : cabeca2, valor)) {
            inserir(cabecaRes, valor);
        }
        atual = atual->proximo;
    } 

    return cabecaRes;
}

// Verifica se duas listas cadastrais são iguais
int saoIguais(Node *cabeca1, Node *cabeca2) {
    int tamanho1 = tamanho(cabeca1);
    int tamanho2 = tamanho(cabeca2);

    if (tamanho1 != tamanho2) {
        return 0;
    }

    Node * atual1;
    atual1 = cabeca1->proximo;

    Node * atual2;
    atual2 = cabeca2->proximo;

    // As duas listas terão o mesmo tamanho dentro do while
    while (atual1 != NULL) {
        if (atual1->conteudo != atual2->conteudo) {
            return 0;
        }
        atual1 = atual1->proximo;
        atual2 = atual2->proximo;
    }

    return 1;
}