#include "Arvore.h"
#include "math.h"

Noh *criarArvore() {
    return NULL;
}

Noh * novoNoh(int valor) {
    Noh *novo = (Noh *) malloc(sizeof(Noh));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
    novo->valor = valor;
    return novo;
}

void inserir(Noh **arvore, int elemento) {
    if ((*arvore) == NULL) {
        *arvore = novoNoh(elemento);
    } else if (elemento <= (*arvore)->valor){
        inserir(&(*arvore)->esq, elemento);
    } else {
        // elemento > (*arvore)->valor
        inserir(&(*arvore)->dir, elemento);
    }
}

int verificarAVL(Noh *arvore, int *result) {
    if (arvore == NULL) {
        return -1;
    }

    if ((*result) == 0) {
        return (*result);
    }

    int alturaEsq = verificarAVL(arvore->esq, result);
    int alturaDir = verificarAVL(arvore->dir, result);

    // Quando result for 0 iremos para de verificar as alturas, por isso o return.
    if ((*result) == 0) {
        return (*result);
    }

    if (alturaEsq > alturaDir) {
        if ((alturaEsq - alturaDir) > 1) {
            (*result) = 0;
        }
        return alturaEsq + 1;
    }
    if ((alturaDir - alturaEsq) > 1) {
        (*result) = 0;
    }
    return alturaDir + 1;
}

// Como depende da quantidade de elementos, então é O(n)
int calcularAltura(Noh *arvore) {
    if (arvore == NULL) {
        return -1;
    }
    int alturaEsquerda = calcularAltura(arvore->esq);
    int alturaDireita = calcularAltura(arvore->dir);
    if (alturaEsquerda > alturaDireita) {
        return alturaEsquerda + 1;
    }
    return alturaDireita + 1;
}

void imprimirArvoreInOrder(Noh *arvore) {
    if (arvore == NULL) {
        return;
    }
    imprimirArvoreInOrder(arvore->esq);
    printf("%d ", arvore->valor); 
    imprimirArvoreInOrder(arvore->dir);
}
