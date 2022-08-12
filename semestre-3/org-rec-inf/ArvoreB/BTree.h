#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct node {
    int size;
    int isLeaf;
    int *keys;
    struct node **pointers;
} Node;

typedef struct tresde {
    Node *root;
} BTree;

BTree *createBTree();
Node *create();
int nodeIsComplete(Node *node);
void insertIncompleteNode(Node *node, int value);
void insert(BTree *tree, int value);
void divideChild(Node *parent, int position, Node *child);
void print(Node *node);
Node *findKey(Node *node, int key, int *position);
