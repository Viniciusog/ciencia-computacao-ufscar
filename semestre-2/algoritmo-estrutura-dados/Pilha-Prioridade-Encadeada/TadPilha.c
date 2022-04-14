#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    char conteudo;
    Node *proximo;
} Node;

typedef struct pilha {
    Node *inicio;
    Node *fim;
    int tam
} Pilha;


Pilha *criar() {
    Pilha *pilha;
    pilha = malloc(sizeof(Pilha));
    pilha->tam = 0;
    return pilha;
}

Node *criarNode(char valor) {
    Node *node = malloc(sizeof(Node));
    node->conteudo = valor;
    return node;
}


void inserir(Pilha *p, char valor) {
    Node *novo = criarNode(valor);
    // Se a pilha estiver vazia
    if (p->tam == 0) {
        novo->proximo = novo;
        p->inicio = novo;
        p->fim = novo;
    } 
    // Se a pilha tiver elemento, iremos verificar se o elemento do início da pilha é menor que o 
    // elemento a ser adicionado e se for, iremos fazer esse novo elemento apontar para o início da pilha e
    // e em seguida, adicionar esse novo elemento no início da pilha
    // Se inicioAtual < novo, novo->proximo = inicioAtual e inicio = novo
    else if (p->tam == 1) {
        // inserir no início da pilha
        if (p->inicio->conteudo <= novo->conteudo) {
            novo->proximo = p->inicio;
            p->inicio->proximo = novo;
            p->inicio = novo;
        } 
        // inserir no fim da pilha
        else {
            p->inicio->proximo = novo;
            novo->proximo = p->inicio;
        }
    } 
    // Se tiver mais do que 1 elemento na pilha 
    else {
        // Se o nosso valor for maior do que o início da pilha, precisaremos inserir no início da pilha
        if (novo->conteudo >= p->inicio) {
            novo->proximo = p->inicio;
            p->inicio = novo;
            p->fim->proximo = p->inicio;
        } 

        Node *atual = p->inicio;
        while (atual->proximo->conteudo > novo->conteudo && atual->proximo != p->inicio) {
            atual = atual->proximo;
        }

        // Inserir no fim da pilha
        if (atual->proximo == p->inicio) {
            novo->proximo = atual->proximo;
            atual->proximo = novo;
            p->fim = atual;
        } 
        // Inserir no meio da fila
        else {
        
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;   

        
    }

}

