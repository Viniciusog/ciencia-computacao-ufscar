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

    printf("\n");
    print(bTree->root);
    printf("\n");
    removeWrapper(&bTree->root, 10);
    print(bTree->root);

    removeWrapper(&bTree->root, 8);
    printf("\n");
    print(bTree->root);
    printf("\n");

    removeWrapper(&bTree->root, 3);
    printf("\n");
    print(bTree->root);
    printf("\n");
    
    removeWrapper(&bTree->root, 3);
    printf("\n");
    print(bTree->root);
    printf("\n");


}