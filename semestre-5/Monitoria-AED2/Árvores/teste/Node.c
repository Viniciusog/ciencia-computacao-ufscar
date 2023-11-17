#include "./Node.h"

#define Q  4

Node *create() {
    return NULL;
}

// Número 3456
// Dígito da posição 0: 3
// Dígito da posição 1: 4
// Dígito da posição 2: 5
// Dígito da posição 3: 6
int getDigitFromKey(int key, int numberDigit) {
  int aux = key / pow(10, (Q-1)-numberDigit);
  int digit = aux % 10;
  return digit;
}

void insertWrapper(Node **tree, int key, void *content) {
    insert(&(*tree), key, content, 0);
}

void insert(Node **tree, int key, void *content, int digit) {
    // se na posição queiremos inserir o nó atual é NULO, então iremos criar um novo nó para esta posição
    // o primeiro nó que será inserido irá cair nesse primeiro if
    if ((*tree) == NULL) {
        Node *newNode = (Node *) malloc(sizeof(Node));
        newNode->content = content;
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        (*tree) = newNode;
    } else if (getDigitFromKey(key, digit) == 0) {
        // então iremos precisar inserir na esquerda do nó atual
        insert(&(*tree)->left, key, content, digit + 1);
    } else if (getDigitFromKey(key, digit) == 1) {
        // então iremos precisar inserir na direita do nó atual
        insert(&(*tree)->right, key, content, digit + 1);
    }
}

void print(Node *node) {
    if (node == NULL) {
        return;
    }
    print(node->left);
    printf("%d ", node->key);
    print(node->right);
}