#include <stdlib.h>
#include <stdio.h>
#include "Tree.c"
int main() {
    Node *node = create();
    /* node = insert(node, 50);
    node = insert(node, 20);
    node = insert(node, 18);
    node = insert(node, 64);
    node = insert(node, 27); 
    
    print(node);
    printf("\n");
    node = rightRotation(node);
    print(node);
    */

   /* 
    node = insert(node, 50);
    node = insert(node, 25);
    node = insert(node, 64);
    node = insert(node, 58);
    node = insert(node, 90);

    print(node);
    printf("\n");
    node = leftRotation(node); 
    
   */

    // TEST LEFT RIGHT ROTATION
    /* node = insert(node, 50);
    node = insert(node, 30);
    node = insert(node, 20);
    node = insert(node, 40);
    node = insert(node, 35);
    node = insert(node, 45);
    node = insert(node, 60);
    node = insert(node, 70);

    print(node);
    printf("\n");
    node = leftRightRotation(node);
    print(node); */

    //TESTE LEFT RIGHT ROTATION
    /*
    node = insert(node, 50, 111);
    node = insert(node, 35, 112);
    node = insert(node, 70, 113);
    node = insert(node, 60, 114);
    node = insert(node, 95, 115);
    node = insert(node, 54, 116);
    node = insert(node, 69, 117);

    print(node);
    printf("\n");
    node = rightLeftRotation(node);
    print(node); 
    */

    Node *tree = create();
    int heightIncreased;
    tree = insertAVL(tree, 50, 111, &heightIncreased);
    tree = insertAVL(tree, 30, 111, &heightIncreased);
    tree = insertAVL(tree, 20, 111, &heightIncreased);
    tree = insertAVL(tree, 10, 111, &heightIncreased);
    tree = insertAVL(tree, 25, 111, &heightIncreased);
    tree = insertAVL(tree, 60, 111, &heightIncreased);
    tree = insertAVL(tree, 5, 111, &heightIncreased);
    tree = insertAVL(tree, 8, 111, &heightIncreased);

  /*   tree = insertAVL(tree, 25, 111, &heightIncreased);
    tree = insertAVL(tree, 22, 111, &heightIncreased); */
    inOrder(tree);    
    printf("\n%d\n", tree->bal);
    printf("\nChave raiz: %d", tree->key);
    printf("\nChave esquerda: %d", tree->left->key);
    printf("\nChave esquerda-esquerda: %d", tree->left->left->key);
    printf("\nChave esquerda-direita: %d", tree->left->right->key);
    printf("\nChave direita: %d", tree->right->key);
    //printf("\nChave direita-esquerda: %d", tree->right->left->key);
    printf("\nChave direita-direita: %d", tree->right->right->key);
    return 0;
}