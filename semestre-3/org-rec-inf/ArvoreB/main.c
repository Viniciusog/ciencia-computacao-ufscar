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
        printf("Chave encontrada! Endereço do nó: %p. Posição da chave: %d\n", node, position);
    } else {
        printf("Chave não encontrada na árvore B.");
    }
}