#include "Fila.h"

Fila *criarFila() {
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    fila->tam = 0;
    fila->primeiro = NULL;
    fila->ultimo = NULL;
}

Node *criarNodeFila(Noh *conteudo) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->conteudo = conteudo;
    node->proximo = NULL;
    return node;
}

void inserirNaFila(Fila *fila, Noh *nohArvoreParaArmazenar) {
    Node *novo = criarNodeFila(nohArvoreParaArmazenar);
    if (fila->tam == 0) {
        fila->primeiro = novo;
        fila->ultimo = novo;
    } else {
        fila->ultimo->proximo = novo;
        fila->ultimo = novo;
    }
    fila->tam++;
}

Node *removerPrimeiroDaFila(Fila *fila) {
    Node *paraRemover = NULL;
    if (fila->tam > 0) {
        paraRemover = fila->primeiro;
        fila->primeiro = paraRemover->proximo;
        fila->tam--;
    }
    return paraRemover;
}

void imprimirFila(Fila *fila) {
    Node *atual = fila->primeiro;
    while (atual != NULL) {
        printf("%d ", atual->conteudo->valor);
        atual = atual->proximo;
    }
}

// Aqui estamos liberando todos os nodes da fila .
// Mas não estamos fazendo o free nos conteúdos desses nodes, pois
// o conteúdo desses nodes são na verdade ponteiros para nós da árvore
void freeConteudoFila(Fila *fila) {
    while (fila->tam > 0) {
        Node *primeiro = removerPrimeiroDaFila(fila);
        free(primeiro);
    }
}