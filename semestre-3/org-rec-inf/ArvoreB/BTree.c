
#include "BTree.h"

// TODO: fazer uma função para criar uma árvore B
// Ao tentar inserir dentro de uma árvore B que acabou de ser criada ela será a raiz
// Entretanto, não temos como inserir dentro de raiz
// entretanto, os nós da raiz não estão apontando para ninguém, então como que iremos
// realizar a inserção de uma chave dentro dessa raiz inicial?
// Será que quando criamos a árvore B o primeiro nó será na verdade uma folha ?
// Eu acho que os ponteiros de cada um dos nós são iniciados automaticamente inicialmente
// ou seja, mesmo que for a primeira raiz ela já terá os ponteiros apontando para nós existentes,
// na qual podemos inserir
BTree *createBTree() {
    BTree *bTree = (BTree *)  malloc(sizeof(BTree *));
    bTree->root = create();
    return bTree;
}

/*
Grau: T
Max size for data array: 2t-1
Min size for data array: t-1

Max size for pointersArray: 2t
Min size for pointersArray: t
*/
Node *create() {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->keys = (int *) malloc((2*T - 1)  * sizeof(int));
    newNode->pointers = (Node **) malloc((2*T) * sizeof(Node *));
    newNode->size = 0;
    newNode->isLeaf = 1;
    return newNode;
}

int nodeIsComplete(Node *node) {
    return node->size == 2*T - 1;
}

void insertIncompleteNode(Node *node, int value) {
    if (node->isLeaf) {
        int index = 0;
        while (index < 2*T - 1 && node->keys[index] < value) {
            index++;
        }   

        for (int i = node->size; i > index; i--) {
            node->keys[i] = node->keys[i - 1];
        }
        node->keys[index] = value;
        node->size++;
        //Gravar nó de volta no disco
    } else { // Estamos em nó interno
        int index = 0;
        while (index < 2*T - 1 && node->keys[index] < value) {
            index++;
        }

        // Após encontrar o index onde o elemento deverá estar, como o nó atual é um nó interno, 
        // então precisaremos inserir dentro de um nó que é apontado pelo ponteiro na posicao index
        Node *subNode = node->pointers[index];

        // Se o nó em que queremos inserir está completo
        if (subNode->size == 2*T - 1) {
            divideChild(node, index, subNode);
            // Se a chave que queremos inserir é menor do que a mediana (Feito pela divisão) que está na posição index,
            // então iremos inserir a chave apartir do nó que está em pointers[index]
            // Se não, iremos inserir a chave apartid o nó que está em pointers[index + 1]
            if (value <= node->keys[index]) {
                insertIncompleteNode(node->pointers[index], value);
            } else {
                insertIncompleteNode(node->pointers[index + 1], value);
            }
        } else {
            // Apenas manda inserir dentro desse sub nó
            insertIncompleteNode(subNode, value);
        }
    }
}

void insert(BTree *tree, int value) {
    Node *root = tree->root;
    // aqui iremos precisar verificar se podemo sinserir o elemento dentro da árvore quando o elemento atual não está completo
    // Se o nó atual não estiver completo então iremos inserir dentor desse nó. Se estiver completo, então iremos ter que dividir o nó atual em duas partes
    // para só então inserir o elemento aí dentro
    // Aqui o nó atual não está completo e portanto podemos inserir dentro dele
    if (root->size < 2*T - 1) {
        insertIncompleteNode(root, value);
    } else { // Se o nó estiver completo
        Node *newRoot = create();
        newRoot->isLeaf = 0;
        newRoot->pointers[0] = root;
        tree->root = newRoot;

        divideChild(newRoot, 0, root);

        insertIncompleteNode(newRoot, value);
    }
}

void divideChild(Node *parent, int position, Node *child) {
    
    Node *childBrother = create();
    childBrother->isLeaf = child->isLeaf;

    // T - 1 significa a posição do meio do array
    // Passar as T - 1 maiores chaves do filho para o novo nó
    for (int i = T - 1 + 1; i < 2*T - 1; i++) {
        childBrother->keys[i - T] = child->keys[i];
    }    

    // Se o filho não for folha, precisamos passar também os ponteiros
    if (!child->isLeaf) {
        for (int i = T - 1 + 1; i < 2*T; i++) {
            childBrother->pointers[i - T] = child->pointers[i];
        }
    }

    // O filho vai ficar com os T - 1 menores chaves
    child->size = T - 1;
    // O irmão vai ficar com os T - 1 maiores chaves
    childBrother->size = T - 1;

    // Adicionar a chave do meio do filho para dentro do pai

    // primeiro iremos ter que arrumar as posições das chaves que estão dentro do pai
    for (int i = 2*T - 1 - 1; i > position; i--) {
        parent->keys[i] = parent->keys[i - 1];
    }

    // segundo iremos ter que arrumar as posições dos ponteiros que estão dentro do pai
    for (int i = 2*T - 1; i > position + 1; i--) {
        parent->pointers[i] = parent->pointers[i - 1];
    }

    parent->keys[position] = child->keys[T - 1];
    parent->pointers[position + 1] = childBrother;
    parent->size++;

    // Gravar os nós pai, filho e novo filho no disco
}

void print(Node *node) {
    if (node->isLeaf) {
        for (int i = 0; i < node->size; i++) {
            printf("%d ", node->keys[i]);
        }
    } else {
        for (int i = 0; i < node->size; i++) {
            print(node->pointers[i]);
            printf("%d ", node->keys[i]);
        }
        // Como tem 1 ponteiro a mais do que chaves
        // temos que imprimir o conteúdo do nó que está nesse último ponteiro
        print(node->pointers[node->size]);
    }
}

Node *findKey(Node *node, int key, int *position) {
    int index  = 0;
    while (index < node->size && node->keys[index] < key) {
        index++;
    }

    if (index == node->size) {
        if (node->isLeaf) {
            return NULL;
        } 
        // Se não for folha, então precisaremos buscar no nó apontado pelo último ponteiro
        else {
            return findKey(node->pointers[index], key, position);
        }
    } else if (node->keys[index] == key) {
        *position = index;
        return node;
    } 
    // Se não for igual à chave e o índice for menor do que node->size, então a chave na posição atual
    // será maior do que a chave que estamos procurando
    else {
        if (node->isLeaf) {
            // Se é folha, não há mais nós para percorrer e portanto, a chave buscada não está na árvore
            return NULL;
        } else {
            return findKey(node->pointers[index], key, position);
        }
    }
}