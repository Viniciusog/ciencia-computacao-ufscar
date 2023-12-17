
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

Node *create() {
    return NULL;
}

Node* insertElement(Node *node, char value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->value = value;
    // Se ainda não tiver elemento na lista
    if (node == NULL) {
        newNode->next = NULL;
    } 
    // Se já tiver elemento na lista
    else {
        newNode->next = node;
    }
    return newNode;
}

Node * removeElement(Node *node, int value) {
    if (node == NULL) {
        return NULL;
    }
    // Se for o primeiro elemento da lista
    if (node->value == value) {
        Node *newHead = node->next;
        free(node);
        return newHead;
    }
    // Se estiver no meio da lista
    Node *atual = node;
    // Dá para fazer isso pois o primeiro elemento já foi tratado
    while (atual->next != NULL && atual->next->value != value) {
        atual = atual->next;
    }

    // if (atual->next == NULL) então percorreu toda a lista e não encontrou o elemento

    // Encontrou o elemento que está o next
    if (atual->next != NULL) {
        Node *toRemove = atual->next;
        atual->next = toRemove->next;
        free(toRemove);
    }
    return node;
} 

void printAll(Node *node) {
    Node *current = node;
    
    printf("\n");

    if (current == NULL) {
        printf("Empty list.");
        return;
    }

    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
}

int main() {
    Node *myNode = create();
    myNode = insertElement(myNode, 8);
    myNode = insertElement(myNode, 9);
    myNode = insertElement(myNode, 4);
    myNode = insertElement(myNode, 7);

    printAll(myNode);

    myNode = removeElement(myNode, 8);
    printAll(myNode);

    myNode = removeElement(myNode, 4);
    printAll(myNode);

    myNode = removeElement(myNode, 7);
    printAll(myNode);

    myNode = removeElement(myNode, 9);
    printAll(myNode);
}