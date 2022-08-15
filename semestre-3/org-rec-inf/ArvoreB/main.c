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

    insert(bTree, 12);
    insert(bTree, 13);
    insert(bTree, 14);
    insert(bTree, 15);
    insert(bTree, 16);
    insert(bTree, 17);
    insert(bTree, 18);

    printf("\n");
    print(bTree->root);
    printf("\nroot size before trying to remove 5: %d\n", bTree->root->size);
    printf("\n");
    removeWrapper(&bTree->root, 5);
    printf("\nroot size after trying to remove 5: %d\n", bTree->root->size);
    print(bTree->root);

    int success = removeWrapper(&bTree->root, 11);
    printf("Sucesso ao tentar remover 11? %d\n", success);

    print(bTree->root);


    /* 
    printf("size root before deleting 8: %d\n", bTree->root->size);
    removeWrapper(&bTree->root, 8);
    printf("\n");
    print(bTree->root);
    printf("\n");
    printf("size root after deleting 8: %d\n", bTree->root->size);

    removeWrapper(&bTree->root, 3);
    printf("\n");
    print(bTree->root);
    printf("\n");
    
    removeWrapper(&bTree->root, 3);
    printf("\n");
    print(bTree->root);
    printf("\n"); */
}