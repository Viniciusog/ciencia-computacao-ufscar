#include <stdlib.h>
#include <stdio.h>

#include "Tree.h"

typedef struct node {
    int bal;
    int key;
    int content;
    Node *left;
    Node *right;
    Node *father;
} Node;

Node *create() {
    return NULL;
}


/**
 ** Caso 0
 *      Se a altura da subárvore não aumentou, então devolve que não houve um aumento da altura
 ** Caso 1
 *      Se a árvore era vazia, então crie um nó com os dois filhos sendo NULL e balanceamento 0
 *      Retorne dizendo a altura aumentou
 ** Caso 2
 *      Se inseriu na subárvore mais baixa e a altura desta aumentou
 *      Mude o balanceamento da raiz para 0 e retorne dizendo que a altura da árvore não aumentou
 ** Caso 3
 *      Se inseriu em qualquer uma das subárvores quando a altura delas eram iguais (bal da raiz sendo 0)
 *      Mude o balanceamento para 1 ou -1 dependendo do lado da inserção
 *      Devolva que a altura da árvore aumentou
 ** Caso 4
 *      Se inseriu na subárvore maior e a altura dela aumentou
 *      Realizar rotações para restaurar as propriedades AVL
 **     Caso 4.1
 *          Após inserir na subárvore da esquerda o balanceamento dela é -1
 *          Realizar rotação da subárvore para a direita.
 * 
 *          OBS (Temos aqui também o caso de inserir na subárvore da direita e o balanceamento dela ser -1)
 *          Realizar rotação dupla direita esquerda
 **     Caso 4.2
 *          Após inserir na subárvore da esquerda o balanceamento dela é 1
 *          Realizar rotação dupla esquerda direita
 *          
 *          OBS (Temos aqui também o caso de inserir na subárvore da direita e o balanceamento dela ser 1)
 *          Realizar rotação da subárvore para a esquerda
 * 
 */

Node *insert(Node *tree, int key, int value) {
    if (tree == NULL) {
        Node *newTree = (Node *) malloc(sizeof(Node));
        newTree->key = key;
        newTree->content = value;
        newTree->father = NULL;
        newTree->left = NULL;   
        newTree->right = NULL;
        return newTree;
    } else if (key < tree->key) {
        tree->left = insert(tree->left, key, value);
        tree->left->father = tree;
        return tree;
    } else if (key > tree->key) {
        tree->right = insert(tree->right, key, value);
        tree->right->father = tree;
        return tree;
    }
}

Node *removeFromTree(Node **tree, int key) {
    if ((*tree) == NULL) {
        return (*tree);
    } else if (key < (*tree)->key) {
        (*tree)->left = removeFromTree(&(*tree)->left, key);
        // i need to return the tree 
    } else if (key > (*tree)->key) {
        (*tree)->right = removeFromTree(&(*tree)->right, key);
        // i need to return the tree
    } 
    // we have found the element
    else {
        // has no child
        if ((*tree)->left == NULL && (*tree)->right == NULL) {
            printf("no child\n");
            free((*tree));
            return NULL;
        } 
        // has right child
        else if ((*tree)->left == NULL) {
            printf("right child\n");
            Node *rightChild = (*tree)->right;
            rightChild->father = (*tree)->father;
            free((*tree));
            return rightChild;
        } 
        // has left child
        else if ((*tree)->right == NULL) {
            printf("left child\n");
            Node *leftChild = (*tree)->left;
            leftChild->father = (*tree)->father;
            free((*tree));
            return leftChild;
        } 
        // has two children
        else {
            Node *nodeHighestValue = getNodeHighestValue((*tree)->left);
            printf("node highest value: %d", nodeHighestValue->content);
            (*tree)->content = nodeHighestValue->content;
            (*tree)->key = nodeHighestValue->key;
            (*tree)->left = removeFromTree(&(*tree)->left, nodeHighestValue->key);
            // i need to return the tree
        }
    }
    return (*tree);
    // if the tree is null
    // if the value is less or equal the node's content
    // if the value is more than the node's content
    // if the value is equal node's content
        // if node has 0 childs
        // if node has 1 child in the left
        // if node has 1 child in the right 
        // if node has 2 childs
}

Node *newNode() {
    Node *new = (Node *) malloc(sizeof(Node));
    new->bal = 0;
    new->father = NULL;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node *insertAVL(Node *node, int key, int value, int *heightIncreased) {
    if (node == NULL) {
        // Caso 1
        Node *new = newNode();
        new->key = key;
        new->content = value;
        *heightIncreased = 1;
        return new;
    } 
    // inserção na esquerda
    else if (key <= node->key) {
        node->left = insertAVL(node->left, key, value, heightIncreased);
        node->left->father = node;
        
        if (*heightIncreased == 1) {
            // Caso 2: se inseriu na menor subárvore
            if (node->bal == 1) {
                node->bal = 0;
                *heightIncreased = 0;
            }

            // Caso 3: se ambas as subárvores tinham a mesma altura
            // Se temos um árvore com apenas dois nós, um nó A raiz e um nó B subárvore de A na esquerda
            // Quando formos inserir um nó na subárvore B, então passará por aqui logo após retornar o nó criado
            else if (node->bal == 0) {
                node->bal = -1;
                *heightIncreased = 1;
            }
            // Caso 4: inseriu na maior subárvore
            else if (node->bal == -1) { 
                // se o balanceamento da árvore é -1, então significa que a subárvore da esquerda está desbalanceada
                // Portanto, o balanceamento da subárvore na esquerda só poderá ser -1 ou 1, pois ela está desbalanceada
                
                // inseriu na esquerda da subárvore da esquerda (os valores de node->left->bal já estão atualizados)
                // Caso 4.1
                if (node->left->bal == -1) {
                    node = rightRotation(node);
                    node->right->bal = 0; // A antiga raiz da árvore agora é filho direito da raiz atual
                } 
                // inseriu na direita da subárvore da esquerda
                // Caso 4.2
                else if (node->left->bal == 1) {
                    node = leftRightRotation(node);
                    
                    // Saberemos onde que inseriu o elemento 
                    
                    if (node->bal == 0) { // Nesse caso, o próprio Z que tinha sido inserido
                        // Se sabemos que a altura aumentou e o balanceamento de Z ficou 0
                        // Então sabemos que o filho direito de Y era na verdade NULL e Z foi inserido
                        // Se a altura aumentou na inserção de Z, então o filho esquerdo de Y também era NULL

                        // Após realizar a rotação dupla, sabemos que o balanceamento da raiz Z será 0
                        // Assim, se Y agora tem ambas as subárvores sendo NULL e o balanceamento da raiz é 0;
                        // Então, sabendo que a subárvore B2 de X é NULL e que o balanceamento de X deve ser 0 para que o
                        // balanceamento da raiz seja 0, então a subárvore C de X também deverá ser NULL
                        node->left->bal = 0;
                        node->right->bal = 0;
                    } else if (node->bal == -1) { //Inseriu na esquerda de Z
                        node->left->bal = 0;
                        node->right->bal = 1;
                    } else if (node->bal == 1) {  //Inseriu na direita de Z
                        node->left->bal = -1;
                        node->right->bal = 0;
                    }
                }
                //Depois das rotações, a raiz estará balanceada
                node->bal = 0;
                // Mesmo depois de realizar todos os processos de rotações, a altura da árvore não terá aumentado
                *heightIncreased = 0;
            }
        }
    } 
    // Inseriu na subárvore da direita
    else {
        node->right = insertAVL(node->right, key, value, heightIncreased);
        node->right->father = node;

        if (*heightIncreased) {
            // Inseriu na menor subárvore
            if (node->bal == -1) {
                node->bal = 0;
                *heightIncreased = 0;
            } 
            // Ambas as subárvores tinham tamanho igual
            else if (node->bal == 0) {
                node->bal = 1;
                *heightIncreased = 1;
            } 
            // Inseriu na maior subárvore
            else { // node->bal == 1    
                // Inseriu node na direita da subárvore da direita
                if (node->right->bal == 1) {
                    node = leftRotation(node);
                    node->left->bal = 0;
                } 
                // Inseriu node na esquerda da subárvore da direita
                else if (node->right->bal == -1) {
                    node = rightLeftRotation(node);

                    // O próprio Z foi o nó inserido.
                    if (node->bal == 0) {
                        node->right->bal = 0;
                        node->left->bal = 0;
                    } else if (node->bal == -1) {
                        // Inseriu em B1 de Z (Esquerda de Z)
                        node->left->bal = 0;
                        node->right->bal = 1;
                    } else if (node->bal == 1) {
                        // Inseriu em B2 de Z (Direita de Z)
                        node->left->bal = -1;
                        node->right->bal = 0;
                    }
                }
                node->bal = 0;
                *heightIncreased = 0;
            }
        }
    }
    return node; // Retornar o nó para que fiquem ligados
}

Node *getNodeHighestValue(Node *tree) {
    if(tree->left == NULL && tree->right == NULL) {
        return tree;
    }
    return getNodeHighestValue(tree->right);
}

// implement null verification
Node *rightRotation(Node *tree) {
    Node *aux = tree->left;
    tree->left = aux->right;
    if (aux->right != NULL) aux->right->father = tree;
    aux->right = tree;
    tree->father = aux;
    return aux;
}

Node *leftRotation(Node *tree) {
    Node *aux = tree->right;
    tree->right = aux->left;
    if (aux->left != NULL) aux->left->father = tree;
    aux->left = tree;
    tree->father = aux;
    return aux;
}

Node *leftRightRotation(Node *tree) {
    tree->left = leftRotation(tree->left);
    return rightRotation(tree);
}

Node *rightLeftRotation(Node *tree) {
    tree->right = rightRotation(tree->right);
    return leftRotation(tree);
}


void inOrder(Node *tree) {
    if (tree == NULL) {
        return;
    }
    inOrder(tree->left);
    printf("%d ", tree->key);
    inOrder(tree->right);
}

void print(Node *tree) {
    if (tree == NULL) {
        return;
    }
    print(tree->left);
    print(tree->right);
    printf("%d ", tree->key);
}