/**
 * Vinícius Guimarães
 * Ciência da Computação - UFSCar
 * 2022
 */

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

// Cria a árvore AVL
Node *create() {
    return NULL;
}

// Inserção normal em árvore binária, está aqui apenas para teste
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


// Se removeu da direita e o balanceamento da raiz era zero, retorna que não houve diminuição do tamanho, então bal da raiz fica -1. Diminuição fica false
// Se removeu da esquerda e o balanceamento da raiz era zero, retorna que não houve diminuição do tamanho, então bal da raiz fica 1. Diminuição fica false

// Se removeu da direita e o balanceamento da raiz era 1, então não há mais diminuição de tamanho e o bal da raiz e das subárvores ficam 0
// Se removeu da direita e o balanceamento da raiz -1 e houve diminuição de tamanho, então:
    // Se o bal da sub árvore da esquerda é -1, então realiza rotação para direita, a subárvore da direita da nova raiz fica com bal = 0 e a raiz também fica com bal = 0
    // Se o bal da subárvore da esquerda é 1, então realiza rotação dupla esquerda direita. 
        // Se o balanceamento da nova raiz é/era 0, então significa que tinha apenas Z. Logo, o bal das subárvores ficam 0
        // Se o balanceamento da nova raiz era 1, então significa que o bal da subárvore da direita fica 0 e o bal da subárvore da esquerda fica -1
        // Se o balanceamento da nova raiz era -1, então significa que o bal da subárvore da direita fica 1 e o bal da subárvore da esquerda fica 0

// Se removeu da esquerda e o balanceamento da raiz era -1, então houve diminuição da tamanho e o bal da raiz e das subárvores ficam 0
// Se removeu da esquerda o balanceamento da raiz era 1, houve diminuição da tamanho, então:
    // Se o bal da subárvore da direita da raiz é 1, então faz rotação para esquerda. O bal da nova raiz fica sendo 0 e o bal da subárvore da esquerda fica 0
    // Se o bal da subárvore da direita da raiz é -1, então faz rotação direita esquerda. 
        // Se o bal da nova raiz é 0, então significa que Z não possuia sub árvores. O bal das subárvores da nova raiz ficam sendo 0
        // Se o bal da nova raiz é 1, então significa que Z tinha b2. O bal da subárvore da direita fica sendo 0 e o bal da subárvore da esquerda fica sendo -1
        // Se o bal da nova raiz é -1, então significa que Z tinha b1. O bal da subárvore da direita fica sendo 1 e o bal da subárvore da esquerda fica sendo 0 

// Se removeu nó com 2 filhos
Node *removeFromTree(Node **tree, int key, int *heightDecreased) {
    if ((*tree) == NULL) {
        return NULL;
    } 
    // Se removeu da esquerda
    else if (key < (*tree)->key) {
        (*tree)->left = removeFromTree(&(*tree)->left, key, heightDecreased);

        // Se a altura diminuiu
        if ((*heightDecreased)) {

            if ((*tree)->bal == 0) {
                (*tree)->bal = 1;
                *heightDecreased = 0;
            }
            else if ((*tree)->bal == -1) {
                (*tree)->bal = 0;
                *heightDecreased = 1;
            }
            else if ((*tree)->bal == 1) {
                // Fazer rotação para a esquerda
                if ((*tree)->right->bal == 1) {
                    (*tree) = leftRotation((*tree));
                    (*tree)->left->bal = 0;
                    (*tree)->bal = 0; // colocar isso em baixo 
                }
                // Fazer rotação dupla direita esquerda
                else if ((*tree)->right->bal == -1) {
                    (*tree) = rightLeftRotation((*tree));

                    // Significa que Z não possuía subárvores
                    if ((*tree)->bal == 0) {
                        (*tree)->left->bal = 0;
                        (*tree)->right->bal = 0;
                    }
                    // Significa que Z possuía subárvore na direita
                    else if ((*tree)->bal == 1) {
                        (*tree)->bal = 0;
                        (*tree)->left->bal = -1;
                        (*tree)->right->bal = 0;
                    }
                    //Significa que Z possuía subárvore na esquerda
                    else if ((*tree)->bal == -1) {
                        (*tree)->bal = 0;
                        (*tree)->left->bal = 0;
                        (*tree)->right->bal = 1;
                    }
                }
                (*tree)->bal = 0;
                *heightDecreased = 0;
            }
        }
    } 
    // Se removeu da direita
    else if (key > (*tree)->key) {
        (*tree)->right = removeFromTree(&(*tree)->right, key, heightDecreased);

        // Se a altura diminuiu
        if (*heightDecreased) {
            if ((*tree)->bal == 0) {
                (*tree)->bal = -1;
                *heightDecreased = 0;
            }
            else if ((*tree)->bal == 1) {
                (*tree)->bal = 0;
                *heightDecreased = 1;
            }
            else if ((*tree)->bal == -1) {
                // Realizar rotação para direita
                if ((*tree)->left->bal == -1) {
                    (*tree) = rightRotation((*tree));
                    (*tree)->right->bal = 0;
                    (*tree)->bal = 0;
                }
                // Realizar rotação dupla esquerda direita
                else if ((*tree)->left->bal == 1) {
                    (*tree) = leftRightRotation((*tree));

                    // Significa que a subárvore Z não tinha subárvores
                    if ((*tree)->bal == 0) {
                        (*tree)->bal = 0;
                        (*tree)->left->bal = 0;
                        (*tree)->right->bal = 0;  
                    } 
                    // Significa que a subárvore Z tinha a subárvore B2
                    else if ((*tree)->bal == 1) {
                        (*tree)->bal = 0;
                        (*tree)->right->bal = 0;
                        (*tree)->left->bal = -1;
                    } 
                    // Significa que a subárvore Z tinha a subárvore B1
                    else if ((*tree)->bal == -1) {
                        (*tree)->bal = 0;
                        (*tree)->left->bal = 0;
                        (*tree)->right->bal = 1;
                    }
                    (*tree)->bal = 0;
                    *heightDecreased = 0;
                }
            }
        }
    } 
    // Encontrou o nó
    else {
        // Sem filhos
        if ((*tree)->left == NULL && (*tree)->right == NULL) {
            free((*tree));
            *heightDecreased = 1;
            return NULL;
        }
        // Se tem filho na esquerda
        else if ((*tree)->right == NULL) {
            Node *leftChild = (*tree)->left;
            leftChild->father = (*tree)->father;
            free((*tree));
            *heightDecreased = 1;
            return leftChild;
        }
        // Se tem filho na direita
        else if ((*tree)->left == NULL) {
            Node *rightChild = (*tree)->right;
            rightChild->father = (*tree)->father;
            free((*tree));
            *heightDecreased = 1;
            return rightChild;
        }
        // Se tem dois filhos
        else {
            // Pega o valor do nó da subárvore da esquerda que contém o maior valor (maior chave)
            // e copia para um nó auxiliar
            Node aux = *getNodeHighestValue((*tree)->left);
            // Precisamos guardar o valor do balanceamento da árvore atual antes que ele seja atualizado pela função de remover
            int balTreeBeforeUpdate = (*tree)->bal;
            // Aqui, como passamos o nó atual para a função de remover, ele já estará com o balanceamento atualizado
            // (Aqui estaremos removendo o nó da subárvore da esquerda com a maior chave)
            (*tree) = removeFromTree(&(*tree), aux.key, heightDecreased);
            
            // Se o nó anterior da raiz era 1 e removemos da esquerda, então 
            // o algoritmo realizará uma rotação para a esquerda ou uma rotação direita esquerda.
            // E a raiz que precisaremos atualizar agora estará no lado esquerdo da nova raiz atualizada pela rotação. 
            if (balTreeBeforeUpdate == 1) {
                (*tree)->left->key = aux.key;
                (*tree)->left->content = aux.content;
                *heightDecreased = 1;
            } 
            // Se o nó raiz tinha balanceamento 0, como não será feito nenhuma rotação pelo algoritmo, então o bal será 1 pois removemos 
            // da esquerda. Além disso, a raiz atual continua a mesma e então iremos atualizar sua chave e valor para a do maior nó
            // da sua subárvore esquerda
            else if (balTreeBeforeUpdate == 0) {
                (*tree)->key = aux.key;
                (*tree)->content = aux.content;
                *heightDecreased = 0;
            }
            // Se o nó da raiz tinha balanceamento -1, então a altura da árvore diminuiu e o pai da raiz atual precisará ser avisado
            // A raiz atual continua sendo a mesma e sua chave e conteúdo será atualizado com os valores do 
            // nó de maior chave da subárvore da esquerda
            else if (balTreeBeforeUpdate == -1) {
                (*tree)->key = aux.key;
                (*tree)->content = aux.content;
                *heightDecreased = 1;
            }
        }
    }
    return (*tree);
}

Node *newNode() {
    Node *new = (Node *) malloc(sizeof(Node));
    new->bal = 0;
    new->father = NULL;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node *getNodeHighestValue(Node *tree) {
    if(tree->left == NULL && tree->right == NULL) {
        return tree;
    }
    return getNodeHighestValue(tree->right);
}

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