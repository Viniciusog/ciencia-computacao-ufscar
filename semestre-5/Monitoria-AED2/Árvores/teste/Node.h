#include <stdio.h>
#include <stdlib.h>


typedef struct node Node;

typedef struct node {
    int key;
    Node *left;
    Node *right;
    void *content;
} Node;


typedef Node *tree;


int getDigitFromKey(int key, int digit);
Node *create();

/* void remove(Node *node, int key);
void find(Node *node, int key); */
void print(Node *node);
void insertWrapper(Node **node, int key, void *content);
void insert(Node **node, int key, void *content, int digit);