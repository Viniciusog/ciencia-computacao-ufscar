#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int main() {
    Node *arvore = create();
    int heightIncreased = 0;

    /* INSERINDO NA ESQUERDA DA RAIZ */
    arvore = insertAVL(arvore, 10, 555, &heightIncreased);
    arvore = insertAVL(arvore, 5, 556, &heightIncreased);
    arvore = insertAVL(arvore, 3, 557, &heightIncreased);

    printf("Árvore: %d\n", arvore->key); // 5
    printf("Sub-esq: %d\n", arvore->left->key); //3
    printf("Sub-dir: %d\n", arvore->right->key); //10

    Node *arvore2 = create();
    heightIncreased = 0;
    arvore2 = insertAVL(arvore2, 10, 555, &heightIncreased);
    arvore2 = insertAVL(arvore2, 5, 555, &heightIncreased);
    arvore2 = insertAVL(arvore2, 7, 555, &heightIncreased);

    printf("Árvore: %d\n", arvore2->key); //7
    printf("Sub-esq: %d\n", arvore2->left->key); //5
    printf("Sub-dir: %d\n", arvore2->right->key); //10

    /* INSERINDO NA DIREITA DA RAIZ */
    Node *arvore3 = create();
    arvore3 = insertAVL(arvore3, 10, 555, &heightIncreased);
    arvore3 = insertAVL(arvore3, 20, 556, &heightIncreased);
    arvore3 = insertAVL(arvore3, 30, 557, &heightIncreased);

    printf("Árvore: %d\n", arvore3->key); // 20
    printf("Sub-esq: %d\n", arvore3->left->key); //10
    printf("Sub-dir: %d\n", arvore3->right->key); //30

    Node *arvore4 = create();
    heightIncreased = 0;
    arvore4 = insertAVL(arvore4, 10, 555, &heightIncreased);
    arvore4 = insertAVL(arvore4, 20, 556, &heightIncreased);
    arvore4 = insertAVL(arvore4, 15, 557, &heightIncreased);

    printf("Árvore: %d\n", arvore4->key); //15
    printf("Sub-esq: %d\n", arvore4->left->key); //10
    printf("Sub-dir: %d\n", arvore4->right->key); //20
}