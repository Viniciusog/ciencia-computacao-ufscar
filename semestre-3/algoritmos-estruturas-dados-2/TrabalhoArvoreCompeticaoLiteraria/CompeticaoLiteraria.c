// Vinícius de Oliveira Guimarães
// Curso: Ciência da Computação
// RA: 802431
// Descrição: O trabalho foi realizado utilizando a árvore AVL para conseguir identificar 
// quais palavras do texto estão entre as selecionadas pelos professores.

// Apenas a inserção da árvore AVL está contida no trabalho, pois era o que precisava.
// O código completo da árvore AVL pode ser encontrada nesse link: 
// https://github.com/Viniciusog/ciencia-computacao-ufscar/tree/main/semestre-3/algoritmos-estruturas-dados-2/Arvore-AVL

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct structWord {
    char *content;
    int points;
} Word;

typedef struct node Node;

typedef struct node {
    int bal;
    Word *word;
    Node *left;
    Node *right;
    Node *parent;
} Node;

// Cria a árvore AVL
Node *create() {
    return NULL;
}

// Retorna 1 dizendo que o elemento está na árvore e 0 dizendo que o elemento não está na árvore
int elementExists(Node *tree, char *value, Node **node) {
    if (tree == NULL) {
        return 0;
    } 
    else if (strcmp(value, tree->word->content) < 0) {
        return elementExists(tree->left, value, &(*node));
    } 
    else if (strcmp(value, tree->word->content) > 0) {
        return elementExists(tree->right, value, &(*node));
    }
    else {
        *node = tree;
        return 1;
    }
}

// Cria um novo nó para a árvore AVL
Node *newNode() {
    Node *new = (Node *) malloc(sizeof(Node));
    new->bal = 0;
    new->parent = NULL;
    new->left = NULL;
    new->right = NULL;
    return new;
}

// Retorna o nó que contém o maior chave
// No caso da árvore AVL, o nó com maior chave será o mais a direita da árvore. 
Node *getNodeHighestValue(Node *tree) {
    if(tree->left == NULL && tree->right == NULL) {
        return tree;
    }
    return getNodeHighestValue(tree->right);
}

// Realiza rotação para a direita e retorna a nova árvore
Node *rightRotation(Node *tree) {
    Node *aux = tree->left;
    tree->left = aux->right;
    if (aux->right != NULL) aux->right->parent = tree;
    aux->right = tree;
    tree->parent = aux;
    return aux;
}

// Realiza rotação para a esquerda e retorna a nova árvore
Node *leftRotation(Node *tree) {
    Node *aux = tree->right;
    tree->right = aux->left;
    if (aux->left != NULL) aux->left->parent = tree;
    aux->left = tree;
    tree->parent = aux;
    return aux;
}

// Realiza rotação dupla esquerda direita e retorna a nova árvore
Node *leftRightRotation(Node *tree) {
    tree->left = leftRotation(tree->left);
    return rightRotation(tree);
}

// Realiza rotação dupla direita esquerda e retorna a nova árvore
Node *rightLeftRotation(Node *tree) {
    tree->right = rightRotation(tree->right);
    return leftRotation(tree);
}

// Insere elemento na árvore AVL, recebendo a palavra e a pontuação da mesma
Node *insertAVL(Node *node, char *value, int points, int *heightIncreased) {
    // Se árvore for vazia
    if (node == NULL) {
        Word *w = (Word *) malloc(sizeof(Word));
        w->content = value;
        w->points = points;

        Node *new = newNode();
        new->word = w;
        *heightIncreased = 1;
        return new;
    } 
    // Inserir nó na esquerda da árvore
    else if (strcmp(value, node->word->content) < 0) {
        node->left = insertAVL(node->left, value, points, heightIncreased);
        node->left->parent = node;
        
        if (*heightIncreased == 1) {
            // Inseriu na menor subárvore
            if (node->bal == 1) {
                node->bal = 0;
                *heightIncreased = 0;
            }
            else if (node->bal == 0) {
                node->bal = -1;
                *heightIncreased = 1;
            }
            // Inseriu na maior subárvore
            else if (node->bal == -1) { 
                if (node->left->bal == -1) {
                    node = rightRotation(node);
                    node->right->bal = 0; // A antiga raiz da árvore agora é filho direito da raiz atual
                } 
                else if (node->left->bal == 1) {
                    node = leftRightRotation(node);
                 
                    if (node->bal == 0) { 
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
                node->bal = 0;
                *heightIncreased = 0;
            }
        }
    } 
    // Inserir nó na direita da árvore
    else if (strcmp(value, node->word->content) > 0) {
        node->right = insertAVL(node->right, value, points, heightIncreased);
        node->right->parent = node;

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

// Faz o free nos elementos alocados dinamicamente da árvore AVL
void destroyAVL(Node *node) {
    if (node == NULL) {
        return;
    }

    destroyAVL(node->left);
    destroyAVL(node->right);

    free(node->word->content);
    free(node->word);
    free(node);
    return; 
}   

// Apenas uma função para simplificar o processo de inserção na árvore AVL
Node * inserAVLWrapper(Node *tree, char *value, int points) {
    int heigthDecreased;
    return insertAVL(tree, value, points, &heigthDecreased);
}

int main() {
    Node *arvore = create();

    int qtdPalavras;
    int qtdAlunos;
    scanf("%d %d", &qtdPalavras, &qtdAlunos);

    // Lê as palavras selecionadas pelos professores e insere na árvore AVL
    for (int i = 0; i < qtdPalavras; i++) { 
        char *palavra = (char *) malloc(30 * sizeof(char)); 
        int pontuacao;
        scanf("%s %d", palavra, &pontuacao);
        arvore = inserAVLWrapper(arvore, palavra, pontuacao);
    }

    Node *nodePalavra;
    // Para cada aluno, lê o texto do mesmo e calcula sua pontuação
    for (int i = 0; i < qtdAlunos; i++) {
        int achouPonto = 0;
        int pontuacaoAluno = 0;
        char *palavra = (char *) malloc(30 * sizeof(char));

        // Continua lendo palavra do texto do aluno enquanto não houver ponto final
        while (!achouPonto) {
            scanf("%s", palavra);

            // Se a palavra lida não for ponto final, verifica se ela está na árvore
            // Se estiver, soma a pontuação da palavra na pontuação do aluno
            // Se não, decrementa 10 da nota do aluno
            if (palavra[0] != '.') {
                if (elementExists(arvore, palavra, &nodePalavra)) {
                    pontuacaoAluno += nodePalavra->word->points;
                } else {
                    pontuacaoAluno -= 10;
                }
            } else {
                achouPonto = 1;
            }
        }
        printf("%d\n", pontuacaoAluno);
        free(palavra);
    }
    destroyAVL(arvore);
}