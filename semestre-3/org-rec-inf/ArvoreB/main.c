#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

int main() {    
    BTree *bTree = createBTree();

    insert(bTree, 8);
    insert(bTree, 7);
    insert(bTree, 6);
    insert(bTree, 7);
    insert(bTree, 9);
    insert(bTree, 5);

    print(bTree->root);
    int position;
    Node *node = findKey(bTree->root, 8, &position);

    if (node != NULL) {
        printf("\nChave encontrada! Endereço do nó: %p. Posição da chave: %d\n", node, position);
    } else {
        printf("\nChave não encontrada na árvore B.");
    }

    insert(bTree, 10);
    insert(bTree, 3);
    insert(bTree, 4);
    insert(bTree, 3);
    insert(bTree, 2);
    insert(bTree, 1);
    insert(bTree, 1);

    bTree->root->pointers[bTree->root->size]->size = 0;

    int success;
    Node *keyNode = getMaxKeyIfPossible(bTree->root, &position, &success);

    if (success) {
        printf("\nSucesso! Podemos pegar a maior chave na posição: %d e endereço do nó %p\nTamanho do nó em que a chave está: %d",
         position, keyNode, keyNode->size);
    } else {
        printf("\nSem sucesso! Não podemos pegar a maior chave na posição: %d\n",
         position);
    }

    keyNode = getMinKeyIfPossible(bTree->root, &position, &success);
    if (success) {
        printf("\nSucesso! Podemos pegar a menor chave na posição: %d, chave: %d\nTamanho do nó em que a chave está: %d",
         position, keyNode->keys[position], keyNode->size);
    } else {
        printf("\nSem sucesso! Não podemos pegar a maior chave na posição: %d. Chave: %d\n",
         position, keyNode->keys[position]);
    }


}