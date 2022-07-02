#include "node.h"
#include <stdlib.h>
#include <stdio.h>

Node *create() {
    return NULL;
}

// Inserir na lista duplamente encadeada
void insert(Node **node, Text t, NodeTree *tree) {
    
    /* printf("\n---------\n");
    print((*node));
    printf("\n---------\n"); */
    NodeTree *newTree = (NodeTree *) malloc(sizeof(NodeTree));
    if (tree == NULL) {
        newTree->left = NULL;
        newTree->right = NULL;
        newTree->content = t.content;
        newTree->key = t.quantity;
    } else {
        printf("Quantity: %d, Key: %d\n", t.quantity, tree->key);
        newTree = tree;
    }

    Node *new = (Node *) malloc(sizeof(Node));
    new->tree = newTree;

    // primeiro elemento a ser inserido
    if ((*node) == NULL) {
        printf("primeiro elemento..\n");
        new->previous = NULL;
        new->next = NULL;
        (*node) = new;
    } else {
        printf("próximos elementos..\n");

        // Se tiver que inserir no primeiro elemento
        if (t.quantity < (*node)->tree->key) {
            printf("Executando aqui\n");
            Node *aux = (*node);
            new->next = aux;
            new->previous = NULL;
            aux->previous = new;
            (*node) = new;
        } 
        // Se tiver que inserir entre elementos
        else {
            // Fazer while para manter a ordem
            Node *current = (*node);
            printf("current: %d\n", current->tree->key);
            while (current->next != NULL && (t.quantity > current->next->tree->key)) {
                current = current->next;
                printf("Current atualizado\n");
            }

            if (current->next != NULL) {
                printf("current->next não é null, inserindo %d\n", new->tree->key);
                Node *aux = current->next;
                current->next = new;
                new->next = aux;
                new->previous = current;
                aux->previous = new;
            } else {
                printf("current->next é null, inserindo %d\n", new->tree->key);
                current->next = new;
                new->next = NULL;
                new->previous = current;
                printf("\n---------\n");
                print((*node));
                printf("\n---------\n");
            }
        }
    }
}

// por algum motivo, quanto tem 7, 10, 11 na lista
// era para ficar sem seguida 11, 17
// porém fica apenas 17


void print(Node *node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->tree->key);
    print(node->next);
}

void printTree(NodeTree *tree) {
    if (tree == NULL) {
        return;
    }   
    printTree(tree->left);
    printf("%d ", tree->key);
    printTree(tree->right);
}

// só tem um elemento e estaremos inserindo outro elemento maior do que este único elemento

Node *removeMin(Node **node) {
    Node *aux = (*node);

    if ((*node) != NULL) {

        (*node) = aux->next;
        if ((*node) != NULL) {
            (*node)->previous = NULL;
        }
        printf("(*aux) = %d\n", (aux)->tree->key);
        if ((*node) != NULL) {
            printf("(*node) = %d\n", (*node)->tree->key);     
        }
        // printf("(*node) = %d\n", (*node)->tree->key);        
    }
    /* if ((*node)->next != NULL){
        printf("\nNode next key: %d\n", (*node)->next->tree->key);
    } else {
        printf("\nNode next == NULL\n");
    } */
    
    printf("\nMin key: %d\n", aux->tree->key);
    return aux;
}

NodeTree *generateHuffmanTree(Node **node) {
    NodeTree *myTree;

    // [6, 8, 10, 13, 4]
    // [4, 6, 8, 10, 13]
    // [8, 10, 10, 13]
    // [10, 13, 18]
    // [18, 23]
    // [41]
    while ((*node)->next != NULL) {
        myTree = (NodeTree *) malloc(sizeof(NodeTree));
        print((*node));
        Node *min1 = removeMin(&(*node));
        Node *min2 = removeMin(&(*node));
        //printf("node after removing min: %d\n", (*node)->tree->key);
        //printf("node after removing min 2: %d\n", (*node)->tree->key);
        myTree->key = min1->tree->key + min2->tree->key;
        myTree->content = NULL;
        if (min1->tree->key <= min2->tree->key) {
            myTree->left = min1->tree;
            myTree->right = min2->tree;
        } else {
            myTree->left = min2->tree;
            myTree->right = min1->tree;
        }
        Text t;
        t.content = NULL;
        t.quantity = myTree->key;
        //printf("node before inserting tree calculated:  %d\n", (*node)->tree->key);
        insert(&(*node), t, myTree);
        printf("node after inserting tree calculated: %d\n", (*node)->tree->key);
        printf("\n");
        //print((*node));
        if ((*node)->next == NULL) {
            printf("\nNext == NULL\n");
        }

        /* free(min1);
        free(min2); */
        printf("\n");
    }
     /* printf("\n");
        print((*node));
        printf("\n"); */
    return myTree;
}