/**
 * @file BTree.c
 * @author Vinícius O. Guimarães (Github: viniciusog)
 * @brief B-Tree implementation with int key
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 */

#include "BTree.h"

/**
 * @brief Cria uma árvore B
 * @return Retorna um ponteiro para a nova árvore B.
 */
BTree *createBTree() {
    BTree *bTree = (BTree *)  malloc(sizeof(BTree *));
    bTree->root = create();
    return bTree;
}

/**
 * @brief Cria um novo nó
 * @return Retorna o novo nó
 * 
 * Grau: T
 * Maior quantidade de chaves: 2t-1
 * Menor quantidade de chaves: t-1
 * 
 * Maior quantidade de ponteiros: 2t
 * Menor quantidade de ponteiros: t
 */
Node *create() {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->keys = (int *) malloc((2*T - 1)  * sizeof(int));
    newNode->pointers = (Node **) malloc((2*T) * sizeof(Node *));
    newNode->size = 0;
    newNode->isLeaf = 1;
    return newNode;
}


/**
 * @brief Recebe a raiz de uma árvore B e manda inserir uma chave
 */
void insert(BTree *tree, int key) {
    Node *root = tree->root;
    // Se o nó atual for nó incompleto, então iremos mandar inserir dentro dele
    if (root->size < 2*T - 1) {
        insertIncompleteNode(root, key);
    } else { 
        // Se o nó estiver completo, então iremos criar uma nova raiz e realizar o 
        // processo de divisão
        Node *newRoot = create();
        newRoot->isLeaf = 0;
        newRoot->pointers[0] = root;
        tree->root = newRoot;

        divideChild(newRoot, 0, root);

        // Em seguida manda inserir a chave a partir da raiz.
        insertIncompleteNode(newRoot, key);
    }
}

/**
 * @brief Manda inserir dentro de nó incompleto
 */
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
    } else { 
        // Estamos em nó interno
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
            // Se não, iremos inserir a chave apartir  do nó que está em pointers[index + 1]
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

/**
 * @brief Divide um nó em dois sub nós
 * Adiciona a mediana do nó para dentro do pai.
 */
void divideChild(Node *parent, int position, Node *child) {
    // Este será o nó da esquerda que receberá as T-1 maiores chaves
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

    // Primeiro iremos ter que arrumar as posições das chaves que estão dentro do pai
    // * Em vez que de começar em 2T-1-1, podemos começar de size e ir enquanto for maior do que posicao
    for (int i = 2*T - 1 - 1; i > position; i--) {
        parent->keys[i] = parent->keys[i - 1];
    }

    // Segundo i remos ter que arrumar as posições dos ponteiros que estão dentro do pai
    for (int i = 2*T - 1; i > position + 1; i--) {
        parent->pointers[i] = parent->pointers[i - 1];
    }

    parent->keys[position] = child->keys[T - 1];
    parent->pointers[position + 1] = childBrother;
    parent->size++;

    // Gravar os nós pai, filho e novo filho no disco
    // Por enquanto deixei no heap mesmo.
}

/**
 * @brief Imprime a árvore B da seguinte maneira: inOrder
 */
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

/**
 * @brief Procura uma chave dentro da árvore
 * @return Retorna o nó que contém a chave (Caso a chave for encontrada)
 * @return Retorna NULL caso a chave não estiver dentro da árvore

 * @param position Caso a chave seja encontrada dentro da árvore B, então esta será a posição que 
 * a chave estará dentro do nó retornado.
 */
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
            // Verifica se a chave está em sub nó
            return findKey(node->pointers[index], key, position);
        }
    }
}

/**
 * @brief Remove uma determinada chave a partir da raiz da árvore B
 * @return Retorna 1 se conseguiu remover com sucesso e 0 caso contrário
 * 
 * @param myNode é um ponteiro de ponteiro pois caso a raiz fique com tamanho 0 devido a um merge, então 
 * iremos precisar a atualizar qual será a nova raiz da árvore.
 */
int removeWrapper(Node **myNode, int key) {
    Node *node = *myNode;
    int index = 0;
    while (index < node->size && node->keys[index] < key) {
        index++;
    }

    if (node->isLeaf) {
        if (index < node->size && node->keys[index] == key) {
            // Se a raiz for folha e a chave estiver nela, então remove normalmente
            for (int i = index; i < node->size - 1; i++) {
                node->keys[i] = node->keys[i + 1];
            }
            return 1;
        } else {
            // Não encontrou a chave dentro da raiz
            return 0;
        }
    } else { 
        // Se a raiz for nó interno

        // Se a chave estiver dentro da raiz
        if (index < node->size && node->keys[index] == key) {
            // Tenta pegar a maior chave da sub árvore da esquerda
            int successLeft = 0;
            if (node->pointers[index]->size > T-1) {
                int pos;
                int success;
                Node *nodeWithKey = getMaxKeyIfPossible(node->pointers[index], &pos, &success);
                if (success) {
                    node->keys[index] = nodeWithKey->keys[pos];
                    successLeft = 1;
                    return removeNode(node, index, node->pointers[index], nodeWithKey->keys[pos]);
                }
            } 

            // Tenta pegar a menor chave da sub árvore da direita
            int successRight = 0;
            if (node->pointers[index + 1]->size > T-1 && !successLeft) {
                int pos;
                int success;
                Node *nodeWithKey = getMinKeyIfPossible(node->pointers[index + 1], &pos, &success);
                if (success) {
                    node->keys[index] = nodeWithKey->keys[pos];
                    successRight = 1;
                    return removeNode(node, index + 1, node->pointers[index + 1], nodeWithKey->keys[pos]);
                }
            } 
            
            // Se não conseguir pegar nem a maior chave da sub árvore da esquerda e nem a menor chave da sub árvore da direita então
            // iremos realizar o merge da chave com as duas sub árvores
            if (!successLeft && !successRight) {
                Node *leftNode = node->pointers[index];
                Node *rigthNode = node->pointers[index + 1];
                mergeNodeToLeft(node, index + 1, rigthNode);
                // Após realizar o merge, manda remover a chave no nó gerado pelo merge
                return removeNode(node, index, leftNode, key);
            }
        } else {
            // Se a chave não estiver na raiz, manda remover de um sub nó
            int success = removeNode(node, index, node->pointers[index], key); 
            // Se após da remoção a raiz tiver tamanho 0 (devido a um merge)  
            // iremos precisar atualizar qual será a nova raiz
            if (node->size == 0) {
                *myNode = node->pointers[0];
            }
            return success;
        }
    }
}


/**
 * @brief Remove chave de dentro de um nó 
 * (A função removeWrapper irá chamar a função removeNode inicialmente)
 * 
 * @return Retorna 1 se conseguiu remover a chave com sucesso e 0 caso contrário.
 */
int removeNode(Node *parent, int position, Node *node, int key) {
    if (node->size > T-1) {
        if (node->isLeaf) {
            int index = 0;
            while (index < node->size && node->keys[index] < key) {
                index++;
            }

            if (index < node->size && node->keys[index] == key) {
                // Se encontrou a chave dentro da folha e ela tem size > T-1, então remove normalmente
                for (int i = index; i < node->size - 1; i++) {
                    node->keys[i] = node->keys[i + 1];
                }
                node->size--;
                return 1;
            } else {
                // Não encontrou a chave na folha, retorna dizendo que não houve sucesso
                return 0;
            }
        } else {
            // Aqui estamos em nó interno
            int index = 0;
            while (index < node->size && node->keys[index] < key) {
                index++;
            }

            // Se a chave estiver dentro do nó interno (Aqui o nó interno terá size > T-1)
            if (index < node->size && node->keys[index] == key) {
                // Verificar se tem como pegar a maior chave da sub árvore da esquerda
                int successLeft = 0;
                if (node->pointers[index]->size > T-1) {
                    int pos;
                    int success;
                    Node *nodeWithKey = getMaxKeyIfPossible(node->pointers[index], &pos, &success);
                    if (success) {
                        node->keys[index] = nodeWithKey->keys[pos];
                        successLeft = 1;
                        return removeNode(node, index, node->pointers[index], nodeWithKey->keys[pos]);
                    }
                } 

                // Verificar se tem como pegar a menor chave da sub árvore da direita
                int successRight = 0;
                if (node->pointers[index + 1]->size > T-1 && !successLeft) {
                    int pos;
                    int success;
                    Node *nodeWithKey = getMinKeyIfPossible(node->pointers[index + 1], &pos, &success);
                    if (success) {
                        node->keys[index] = nodeWithKey->keys[pos];
                        successRight = 1;
                        return removeNode(node, index + 1, node->pointers[index + 1], nodeWithKey->keys[pos]);
                    }
                } 
                
                // Se não conseguiu pegar a maior chave da sub árvore da esquerda e nem a menor chave da sub árvore da direita então
                // iremos realizar o merge entre a chave no nó atual e as sub árvores da esquerda e da direita
                if (!successLeft && !successRight) {
                    Node *leftNode = node->pointers[index];
                    Node *rigthNode = node->pointers[index + 1];
                    mergeNodeToLeft(node, index + 1, rigthNode);
                    return removeNode(node, index, leftNode, key);
                }
            } else {
                // Se estamos dento do sub nó e a chave não está dentro do nosso nó, então manda remover 
                // do sub nó que está na posição index encontrada
                return removeNode(node, index, node->pointers[index], key);
            }
        }
    } else { // Nó tem size <= T-1
        if (position == 0 && parent->pointers[position + 1]->size > T-1) {
            // Estamos na posição 0 e iremos pegar emprestado do nó da direita
            borrowFromRight(parent, position, node);
            return removeNode(parent, position, node, key);
        } else if (position == 0 && parent->pointers[position + 1]->size <= T-1) {
            // Estamos na posição 0 e iremos realizar merge com o nó da direita
            Node *rightBrother = parent->pointers[position + 1];
            mergeNodeToLeft(parent, position + 1, rightBrother);
            return removeNode(parent, position, node, key);
        }
        else if (position == parent->size && parent->pointers[position - 1]->size > T-1) {
            // Se estamos na última posição possível do nó (position == size) e iremos pegar emprestado do nó da esquerda
            borrowFromLeft(parent, position, node);
            return removeNode(parent, position, node, key);
        } else if (position == parent->size && parent->pointers[position - 1]->size <= T-1)  {
            // Se estamos na última posição possível do nó (position == size) e iremos realizar merge com nó da esquerda
            Node *leftBrother = parent->pointers[position - 1];
            mergeNodeToLeft(parent, position, node);
            // Obs: Pode acontecer da raiz ficar com tamanho 0 e por isso, precisaremos atualizar qual será a nova raiz
            // dentro da função removeWrapper após receber o retorno da remoção.
            return removeNode(parent, position - 1, leftBrother, key);
        }
        else { // Estamos nas posições não extremas do array de ponteiros
            if (parent->pointers[position - 1]->size > T-1) {
                // Pegar emprestado do nó da esquerda
                borrowFromLeft(parent, position, node);
                return removeNode(parent, position, node, key);
            } else if (parent->pointers[position + 1]->size > T-1) {
                // Pegar emprestado do nó da direita
                borrowFromRight(parent, position, node);
                return removeNode(parent, position, node, key);
            } else {
                // Fazer merge com o nó da esquerda
                Node *leftBrother = parent->pointers[position - 1];
                mergeNodeToLeft(parent, position, node);
                return removeNode(parent, position - 1, leftBrother, key);
            }
        }
    }
}

/**
 * @brief Pega chave emprestada do nó da direita e coloca em "node"
 * A primeira chave do nó da direita é passada para o pai e a chave do pai em position é passado para o "node"
 */
void borrowFromRight(Node *parent, int position, Node *node) {
    Node *rightBrother = parent->pointers[position + 1];
    // Passa a chave do pai em position para "node"
    node->keys[node->size] = parent->keys[position];
    node->size++;
    // Passa a primeira chave do nó da direita para o pai
    parent->keys[position] = rightBrother->keys[0];

    // Arruma as chaves do nó da direita
    for (int i = 0; i < rightBrother->size - 1; i++) {
        rightBrother->keys[i] = rightBrother->keys[i + 1];
    }

    // Se o nó da direita for nó interno
    if (!rightBrother->isLeaf) {
        // Passa o ponteiro da posição 0 do nó interno para "node"
        node->pointers[node->size] = rightBrother->pointers[0];

        // Arruma os ponteiros do nó da direita
        for (int i = 0; i < rightBrother->size; i++) {
            rightBrother->pointers[i] = rightBrother->pointers[i + 1];
        }
    }
}

/**
 * @brief Pega chave emprestada do nó da esquerda e coloca em "node"
 * A última chave do nó da esquerda é passado para o pai e a chave do pai em position-1 é passado para o "node"
 */
void borrowFromLeft(Node *parent, int position, Node *node) {
    Node *leftBrother = parent->pointers[position - 1];            
    // Passa as chaves do nó atual uma posição para direita
    for (int i = node->size; i > 0; i--){
        node->keys[i] = node->keys[i-1];
    }
    node->keys[0] = parent->keys[position - 1];

    // Se for nó interno, passa os ponteiros uma posição para a direita
    if (!node->isLeaf) {
        for (int i = node->size + 1; i > 0; i--) {
            node->pointers[i] = node->pointers[i - 1];
        }
    }
    node->size++;

    // Passa para o pai, a última chave do nó da esquerda
    parent->keys[position - 1] = leftBrother->keys[leftBrother->size - 1];
    // Se for nó interno então pega o último ponteiro do nó da esquerda e coloca na posição 0 de "node"
    if (!node->isLeaf) {
        node->pointers[0] = leftBrother->pointers[leftBrother->size];
    }
    leftBrother->size--;
}

/**
 * @brief Realiza o merge de um nó para a esquerda.
 * Ou seja, os elementos de "node" irão passar para o nó que está na esquerda de "node". 
 * (Lembrando que uma das chaves do pai também fará parte do merge)
 */
void mergeNodeToLeft(Node *parent, int position, Node *node) {
    Node *leftBrother = parent->pointers[position - 1];
    leftBrother->keys[leftBrother->size] = parent->keys[position - 1];
    leftBrother->size++;
    
    // Passa as chaves de "node" e passa para o seu irmão da esquerda
    for (int i = 0; i < node->size; i++) {
        leftBrother->keys[leftBrother->size + i] = node->keys[i];
    }

    // Se for nó interno, passa os ponteiros de "node" para o seu irmão da esquerda
    if (!node->isLeaf) {
        for (int i = 0; i <= node->size; i++) {
            leftBrother->pointers[leftBrother->size + i] = node->pointers[i];
        }
    }
    leftBrother->size += node->size;
    node->size = 0;

    // Arruma as chaves do nó pai
    for (int i = position - 1; i < parent->size - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
    }

    // Arruma os ponteiros do nó pai
    for (int i = position; i < parent->size; i++) {
        parent->pointers[i] = parent->pointers[i + 1];
    }
    parent->size--;
}

/**
 * @brief Retorna a maior chave de uma árvore
 * @return O retorno é um ponteiro para o nó que contém a maior chave
 * @return A variável position indica a posição da maior chave dentro do nó
 * @return A variável success indica se é possível pegar a maior chave de dentro do nó
 
 Se o nó atual for folha e tiver tamanho maior do que T - 1, então é possível pegar a maior chave
 Se o nó atual for folha e tiver tamanho menor ou igual a T - 1, então não é possível pegar a maior chave
 Se o nó for interno, então iremos verificar se o nó apontado pelo último ponteiro tem tamanho maior do que 0
    Se tiver, então iremos chamar a função para buscar a maior chave lá dentro desse sub nó
    Se não, ou seja, se o último nó apontado por ponteiros tiver tamanho 0, então iremos verificar o tamanho do nó atual
        Se o nó atual tiver tamanho maior do que T - 1 e o último sub nó tiver tamanho 0, então conseguiremos pegar a maior
        chave do nó atual.
        Se não, ou seja, nó atual tem tamanho menor ou igual a T - 1 e o último sub nó tiver tamanho 0, então não conseguiremos
        pegar a última chave
 */
Node *getMaxKeyIfPossible(Node *node, int *position, int *success) {
    if (node->isLeaf && node->size > T - 1) {
        *position = node->size - 1;
        *success = 1;
        return node;
    } else if (node->isLeaf && node->size <= T - 1)  {
        *position = node->size - 1;
        *success = 0;
        return NULL;
    }   
    else if (!node->isLeaf) {
        if (node->pointers[node->size]->size > 0) {
            return getMaxKeyIfPossible(node->pointers[node->size], position, success);
        } else if (node->pointers[node->size]->size == 0 && node->size > T - 1) {
            *position = node->size - 1;
            *success = 1;
            return node;
        } else if (node->pointers[node->size]->size == 0 && node->size <= T - 1) { 
            *position = node->size - 1;
            *success = 0;
            return NULL;
        }
    }
}

/**
 * @brief Retorna a menor chave de uma árvore
 * @return O retorno é um ponteiro para o nó que contém a menor chave
 * @return A variável position indica a posição da menor chave dentro do nó
 * @return A variável success indica se é possível pegar a menor chave de dentro do nó
 * 
 * Se o nó for folha, então retorna a chave da posição 0
 * Se o nó for interno, então verifica se o nó apontado pelo ponteiro da posição 0 tem tamanho > 0
 *  Se tiver, então iremos mandar procurar a menor chave desse sub nó na posição 0
 *  Se não, verificaremos se o nó atual tem tamanho > T-1
 *      Se tiver, então conseguiremos pegar a menor chave
 *      Se não tiver, então não conseguiremos pegar a menor chave
 */
Node *getMinKeyIfPossible(Node *node, int *position, int *success) {
    if (node->isLeaf && node->size > T - 1) {
        *success = 1;
        *position = 0;
        return node;
    } else if (node->isLeaf && node->size <= T - 1){
        *success = 0;
        *position = 0;
        return node;
    } else if (!node->isLeaf) {
        if (node->pointers[0]->size > 0) {
            return getMinKeyIfPossible(node->pointers[0], position, success);
        } else if (node->pointers[0]->size == 0 && node->size > T - 1) {
            *success = 1;
            *position = 0;
            return node;
        } else if (node->pointers[0]->size == 0 && node->size <= T - 1) {
            *success = 0;
            *position = 0;
            return NULL;
        }
    } 
}