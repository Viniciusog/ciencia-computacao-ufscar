/**
 * Vinícius Guimarães
 * Ciência da Computação - UFSCar
 * 2022
 */

#ifndef AVL_H
#define AVL_H

typedef struct node Node;

typedef struct node {
    int bal;
    int key;
    int content;
    Node *left;
    Node *right;
    Node *parent;
} Node;


Node *create();
Node *newNode();
Node *insert(Node *tree, int key, int valor);
Node *insertAVL(Node *tree, int key, int valor, int *heightIncreased);
Node *removeFromTree(Node **tree, int valor, int *heightDecreased);
void inOrder(Node *tree);
void print(Node *tree);
Node *getNodeHighestValue(Node *tree);
Node *rightRotation(Node *tree);
Node *leftRotation(Node *tree);
Node *leftRightRotation(Node *tree);
Node *rightLeftRotation(Node *tree);
int getHeight(Node *tree);

#endif