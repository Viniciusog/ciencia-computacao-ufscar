#include <stdlib.h>
#include <stdio.h>
#include "Tree.c"
int main() {
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
    printf("APÓS INSERIR OS ELEMENTOS\n");
    inOrder(tree);    
    printf("\nBalanceamento da raiz: %d", tree->bal);
    printf("\nChave raiz: %d", tree->key);
    printf("\nChave esquerda: %d", tree->left->key);
    printf("\nChave esquerda-esquerda: %d", tree->left->left->key);
    printf("\nChave esquerda-direita: %d", tree->left->right->key);
    printf("\nChave direita: %d", tree->right->key);
    //printf("\nChave direita-esquerda: %d", tree->right->left->key);
    printf("\nChave direita-direita: %d", tree->right->right->key);

    int heightDecreased;
    removeFromTree(&tree, 5, &heightDecreased);
    printf("\n\nAPÓS REMOVER o 5\n");
    inOrder(tree);
    printf("\nBal da raiz: %d", tree->bal);
    printf("\nChave raiz: %d", tree->key);
    printf("\nChave esquerda: %d", tree->left->key);
    printf("\nChave esquerda-esquerda: %d", tree->left->left->key);
    printf("\nChave esquerda-direita: %d", tree->left->right->key);
    printf("\nChave direita: %d", tree->right->key);
    //printf("\nChave direita-esquerda: %d", tree->right->left->key);
    printf("\nChave direita-direita: %d", tree->right->right->key);

    removeFromTree(&tree, 8, &heightDecreased);
    printf("\n\nAPÓS REMOVER o 8\n");
    inOrder(tree);
    printf("\nBal da raiz: %d", tree->bal);
    printf("\nChave raiz: %d", tree->key);
    printf("\nChave esquerda: %d", tree->left->key);
    printf("\nChave esquerda-esquerda: %d", tree->left->left->key);
    printf("\nChave esquerda-direita: %d", tree->left->right->key);
    printf("\nChave direita: %d", tree->right->key);
    //printf("\nChave direita-esquerda: %d", tree->right->left->key);
    printf("\nChave direita-direita: %d", tree->right->right->key);

    removeFromTree(&tree, 20, &heightDecreased);
    printf("\n\nAPÓS REMOVER o 20\n");
    inOrder(tree);
    printf("\nBal da raiz: %d", tree->bal);
    printf("\nChave raiz: %d", tree->key);

    if (tree->left != NULL) {
      printf("\nChave esquerda: %d", tree->left->key);

      if (tree->left->left != NULL) {
        printf("\nChave esquerda-esquerda: %d", tree->left->left->key);
      } 

      if (tree->left->right != NULL) {
        printf("\nChave esquerda-direita: %d", tree->left->right->key);
      }
    }

    if (tree->right != NULL) {
      printf("\nChave direita: %d", tree->right->key);

      if (tree->right->right != NULL) {
        printf("\nChave direita-direita: %d", tree->right->right->key);
      }
    }


    removeFromTree(&tree, 25, &heightDecreased);
    printf("\n\nAPÓS REMOVER o 25\n");
    inOrder(tree);
    printf("\nBal da raiz: %d", tree->bal);
    printf("\nChave raiz: %d", tree->key);

    if (tree->left != NULL) {
      printf("\nChave esquerda: %d", tree->left->key);

      if (tree->left->left != NULL) {
        printf("\nChave esquerda-esquerda: %d", tree->left->left->key);
      } 

      if (tree->left->right != NULL) {
        printf("\nChave esquerda-direita: %d", tree->left->right->key);
      }
    }

    if (tree->right != NULL) {
      printf("\nChave direita: %d", tree->right->key);

      if (tree->right->right != NULL) {
        printf("\nChave direita-direita: %d", tree->right->right->key);
      }
    }


    removeFromTree(&tree, 10, &heightDecreased);
    printf("\n\nAPÓS REMOVER o 10\n");
    inOrder(tree);
    printf("\nBal da raiz: %d", tree->bal);
    printf("\nChave raiz: %d", tree->key);

    if (tree->left != NULL) {
      printf("\nChave esquerda: %d", tree->left->key);

      if (tree->left->left != NULL) {
        printf("\nChave esquerda-esquerda: %d", tree->left->left->key);
      } 

      if (tree->left->right != NULL) {
        printf("\nChave esquerda-direita: %d", tree->left->right->key);
      }
    }

    if (tree->right != NULL) {
      printf("\nChave direita: %d", tree->right->key);

      if (tree->right->right != NULL) {
        printf("\nChave direita-direita: %d", tree->right->right->key);
      }
    }

    tree = insertAVL(tree, 55, 111, &heightIncreased);
    printf("\n\nAPÓS INSERIR o 55\n");
    inOrder(tree);    
    printf("\nBalanceamento da raiz: %d", tree->bal);
    printf("\nChave raiz: %d", tree->key);
    if (tree->left != NULL) {
      printf("\nChave esquerda: %d", tree->left->key);

      if (tree->left->left != NULL) {
        printf("\nChave esquerda-esquerda: %d", tree->left->left->key);
      } 

      if (tree->left->right != NULL) {
        printf("\nChave esquerda-direita: %d", tree->left->right->key);
      }
    }

    if (tree->right != NULL) {
      printf("\nChave direita: %d", tree->right->key);

      if (tree->right->right != NULL) {
        printf("\nChave direita-direita: %d", tree->right->right->key);
      }
      if (tree->right->left != NULL) {
        printf("\nChave direita-esquerda: %d", tree->right->left->key);
      }
    }
    
    
    removeFromTree(&tree, 24, &heightDecreased);
    printf("\n\nAPÓS REMOVER o 24\n");
    inOrder(tree);
    printf("\nBal da raiz: %d", tree->bal);
    printf("\nChave raiz: %d", tree->key);

    if (tree->left != NULL) {
      printf("\nChave esquerda: %d", tree->left->key);

      if (tree->left->left != NULL) {
        printf("\nChave esquerda-esquerda: %d", tree->left->left->key);
      } 

      if (tree->left->right != NULL) {
        printf("\nChave esquerda-direita: %d", tree->left->right->key);
      }
    }

    if (tree->right != NULL) {
      printf("\nChave direita: %d", tree->right->key);

      if (tree->right->right != NULL) {
        printf("\nChave direita-direita: %d", tree->right->right->key);
      }
    }
    
    return 0;
}