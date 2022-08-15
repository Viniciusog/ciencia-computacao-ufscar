
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
    // todo: Em vez que de começar em 2T-1-1, podemos começar de size e ir enquanto for maior do que posicao
    for (int i = 2*T - 1 - 1; i > position; i--) {
        parent->keys[i] = parent->keys[i - 1];
    }

    // segundo iremos ter que arrumar as posições dos ponteiros que estão dentro do pai
    // todo: em vez de começar em size + 1 (pois temos um ponteiro a mais) e continuar enquanto for maior do que 
    // todo: posicao + 1 (pois temos que arrumar todos os ponteiro que estão na direita da posicao);
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

// se a chave estiver em nó folha, remova normalmente caso tiver tamanho > T - 1
// se a chave estiver em nó folha e o nó tiver size <= T-1, tente pegar chave emprestada da esquerda
    // ou da direita. Se nenhuma dessas opções funcionar, faz o merge. e manda remover a partir do nó atual (verificar qual a posição)
// se a chave estiver em nó interno e tiver como pegar emprestado ou fazer o merge com algum nó irmão, então faça
    // se não tiver como, então verifica se a partir do nó atual tem como realizar uma rotação com o sub nó da esquerda ou com
    // o sub nó da direita. Se tiver como, então faz, se não, ralizar o merge da posição do nó atual com o sub nó da esquerda e o 
    // sub nó da direita
// se a chave estiver em nó interno e o nó tiver size > T-1, 

int removeWrapper(Node **myNode, int key) {
    Node *node = *myNode;
    int index = 0;
    while (index < node->size && node->keys[index] < key) {
        index++;
    }

    if (node->isLeaf) {
        printf("wrapper is leaf\n");
        if (index < node->size && node->keys[index] == key) {
            // ajustar chaves
            for (int i = index; i < node->size - 1; i++) {
                node->keys[i] = node->keys[i + 1];
            }
            return 1;
        } else {
            return 0;
        }
    } else {
        printf("wrapper is internal node\n");
        if (index < node->size && node->keys[index] == key) {
            printf("index < node->size && node->keys[index] == key\n");
            int successLeft = 0;
            // pegar a maior chave da sub árvore da esquerda
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

            int successRight = 0;
            // pegar a menor chave da sub árvore da direita
            if (node->pointers[index + 1]->size > T-1 && !successLeft) {
                printf("node->pointers[index + 1]->size > T-1 && !successLeft\n");
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
            // iremos realizar o merge entre essas duas sub árvores
            if (!successLeft && !successRight) {
                printf("!successLeft && !successRight\n");
                Node *leftNode = node->pointers[index];
                Node *rigthNode = node->pointers[index + 1];
                mergeNodeToLeft(node, index + 1, rigthNode);
                return removeNode(node, index, leftNode, key);
            }
            // pegar a maior chave da subárvore esquerda e colocar na posicao index
            // se não tiver como, tentar pegar a menor chave da subárvore da direita
            // se também não tiver como, então teremos que realizar o merge

        } else {
            printf("index é igual ao size ou a chave na posição index é maior do que estamos procurando\n");
            printf("Index wrapper: %d \n", index);
            int success = removeNode(node, index, node->pointers[index], key);   
            if (node->size == 0) {
                printf("node->size == 0 Wrapper\n");
                *myNode = node->pointers[0];
            }
            printf("success wrapper: %d\n", success);
            return success;
        }
    }
}

void borrowFromRight(Node *parent, int position, Node *node) {
    Node *rightBrother = parent->pointers[position + 1];
    node->keys[node->size] = parent->keys[position];
    node->size++;
    parent->keys[position] = rightBrother->keys[0];

    // arrumar as chaves do irmão da direita
    for (int i = 0; i < rightBrother->size - 1; i++) {
        rightBrother->keys[i] = rightBrother->keys[i + 1];
    }

    // se o irmão da direita for nó interno, então iremos precisar pegar o ponteiro da posição 0 dele
    // e colocar no nosso nó na posição size e em seguida arrumar os ponteiro do nó da direita
    if (!rightBrother->isLeaf) {
        node->pointers[node->size] = rightBrother->pointers[0];

        // arrumar os ponteiros do irmão da direita
        for (int i = 0; i < rightBrother->size; i++) {
            rightBrother->pointers[i] = rightBrother->pointers[i + 1];
        }
    }
}

void borrowFromLeft(Node *parent, int position, Node *node) {
    Node *leftBrother = parent->pointers[position - 1];            
    // passar as chaves do nó atual uma posição para direita
    for (int i = node->size; i > 0; i--){
        node->keys[i] = node->keys[i-1];
    }
    node->keys[0] = parent->keys[position - 1];

    // passar os ponteiros uma posição para a direita
    if (!node->isLeaf) {
        for (int i = node->size + 1; i > 0; i--) {
            node->pointers[i] = node->pointers[i - 1];
        }
    }
    node->size++;

    parent->keys[position - 1] = leftBrother->keys[leftBrother->size - 1];
    if (!node->isLeaf) {
        node->pointers[0] = leftBrother->pointers[leftBrother->size];
    }
    leftBrother->size--;
}

void mergeNodeToLeft(Node *parent, int position, Node *node) {
    Node *leftBrother = parent->pointers[position - 1];
    //leftBrother->keys[leftBrother->size - 1] = parent->keys[position - 1];
    leftBrother->keys[leftBrother->size] = parent->keys[position - 1];
    leftBrother->size++;
    
    for (int i = 0; i < node->size; i++) {
        leftBrother->keys[leftBrother->size + i] = node->keys[i];
    }

    if (!node->isLeaf) {
        for (int i = 0; i <= node->size; i++) {
            leftBrother->pointers[leftBrother->size + i] = node->pointers[i];
        }
    }
    leftBrother->size += node->size;
    node->size = 0;
    //arrumar as chaves do nó pai
    for (int i = position - 1; i < parent->size - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
    }

    // arrumar os ponteiros do nó pai
    for (int i = position; i < parent->size; i++) {
        parent->pointers[i] = parent->pointers[i + 1];
    }
    parent->size--;
}


int removeNode(Node *parent, int position, Node *node, int key) {
    if (node->size > T-1) {
        if (node->isLeaf) {
            int index = 0;
            while (index < node->size && node->keys[index] < key) {
                index++;
            }

            if (index < node->size && node->keys[index] == key) {
                // remover da folha
                for (int i = index; i < node->size - 1; i++) {
                    node->keys[i] = node->keys[i + 1];
                }
                node->size--;
                // retornar dizendo que houve sucesso
                return 1;
            } else {
                // não encontrou a chave na folha
                return 0;
            }
        } else {
            int index = 0 ;

            while (index < node->size && node->keys[index] < key) {
                index++;
            }

            if (index < node->size && node->keys[index] == key) {
                int successLeft = 0;
                // pegar a maior chave da sub árvore da esquerda
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

                int successRight = 0;
                // pegar a menor chave da sub árvore da direita
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
                // iremos realizar o merge entre essas duas sub árvores
                if (!successLeft && !successRight) {
                    Node *leftNode = node->pointers[index];
                    Node *rigthNode = node->pointers[index + 1];
                    mergeNodeToLeft(node, index + 1, rigthNode);
                    return removeNode(node, index, leftNode, key);
                }
            } else {
                // mandar remover no sub nó
                return removeNode(node, index, node->pointers[index], key);
            }
            // verificar como realizar a remoção de chave que está em nó com size > T-1
            // lembro que tinha que verificar se a subárvore da esquerda ou a subárvore da direita tinham size > T -1
            // para conseguir pegar uma chave (maior da esquerda ou menor da direita) para substituir no lugar a chave a ser removida
            // e caso não tiver como pegar nenhuma chave das subárvores, então iria fazer merge da chave a ser removida, com as subárvores;
            // da esquerda e da direita
            // e mandar remover o nó da árvore gerada pelo merge
        }
    } else {
        // pegar emprestado do nó da direita
        if (position == 0 && parent->pointers[position + 1]->size > T-1) {
            printf("0 - pegando emprestado do nó na direita\n");
            borrowFromRight(parent, position, node);
            return removeNode(parent, position, node, key);
        } else if (position == 0 && parent->pointers[position + 1]->size <= T-1) {
            printf("0 - merge com nó na direita\n");
            // ter que fazer merge com nó da direita
            Node *rightBrother = parent->pointers[position + 1];
            // vamos fazer o merge do nó da direita no nosso nó atual (que é o nó da esquerda)
            mergeNodeToLeft(parent, position + 1, rightBrother);
            return removeNode(parent, position, node, key);
        }
        // iremos juntar o nosso nó atual com o nó da esquerda
        // isso é a mesma coisa que juntar o nó da esquerda com o nosso nó atual
        else if (position == parent->size && parent->pointers[position - 1]->size > T-1) {
            printf("size - pegando emprestado do nó na esquerda\n");
            borrowFromLeft(parent, position, node);
            return removeNode(parent, position, node, key);
        } else if (position == parent->size && parent->pointers[position - 1]->size <= T-1)  {
            //todo:está dando erro aqui 
            printf("size - merge com nó na esquerda\n");
            // ter que fazer merge com nó da esquerda
            Node *leftBrother = parent->pointers[position - 1];
            mergeNodeToLeft(parent, position, node);
            // lembrando que aqui a raiz pode ter tamanho 1 por conta do merge e por isso, no removeWrapper precisaremos verificar se a raiz
            // tem tamanho 0 e atualizar a nova raiz caso isso acontecer
            return removeNode(parent, position - 1, leftBrother, key);
        }
        else {
            printf("if - position > 0 e position < size\n");
            if (parent->pointers[position - 1]->size > T-1) {
                printf("> 0 e < size - pegando emprestado da esquerda\n");
                borrowFromLeft(parent, position, node);
                return removeNode(parent, position, node, key);
            } else if (parent->pointers[position + 1]->size > T-1) {
                printf("> 0 e < size - pegando emprestado da direita\n");
                borrowFromRight(parent, position, node);
                return removeNode(parent, position, node, key);
            } else {
                printf("> 0 e < size - merge com nó na esquerda");
                // fazer merge com o nó da esquerda
                Node *leftBrother = parent->pointers[position - 1];
                mergeNodeToLeft(parent, position, node);
                return removeNode(parent, position - 1, leftBrother, key);
            }
        }
    }
}

// Retorna a maior chave de uma árvore de chaves
// Se o nó atual for folha e tiver tamanho maio do que T - 1, então é possível pegar a maior chave
// Se o nó atual for folha e tiver tamanho menor ou igual a T - 1, então não é possível pegar a maior chave
// Se o nó for interno, então iremos verificar se o nó apontado pelo último ponteiro tem tamanho maior do que 0
    // Se tiver, então iremos chamar a função para buscar a maior chave lá dentro desse sub nó
    // Se não, ou seja, se o último nó apontado por ponteiros tiver tamanho 0, então iremos verificar o tamanho do nó atual
        // Se o nó atual tiver tamanho maior do que T - 1 e o último sub nó tiver tamanho 0, então conseguiremos pegar a maior
        // chave do nó atual.
        // Se não, ou seja, nó atual tem tamanho menor ou igual a T - 1 e o último sub nó tiver tamanho 0, então não conseguiremos
        // pegar a última chave
Node *getMaxKeyIfPossible(Node *node, int *position, int *success) {
    if (node->isLeaf && node->size > T - 1) {
        printf("\nnode->isLeaf && node->size > T - 1\n");
        *position = node->size - 1;
        *success = 1;
        return node;
    } else if (node->isLeaf && node->size <= T - 1)  {
        printf("\nnode->isLeaf && node->size <= T - 1\n");
        *position = node->size - 1;
        *success = 0;
        return NULL;
    }   
    else if (!node->isLeaf) {
        printf("\n!node->isLeaf\n");
        if (node->pointers[node->size]->size > 0) {
            printf("\nnode->pointers[node->size]->size > 0\n");
            return getMaxKeyIfPossible(node->pointers[node->size], position, success);
        } else if (node->pointers[node->size]->size == 0 && node->size > T - 1) {
            printf("\nnode->pointers[node->size]->size == 0 && node->size > T - 1\n");
            *position = node->size - 1;
            *success = 1;
            return node;
        } else if (node->pointers[node->size]->size == 0 && node->size <= T - 1) { 
            printf("\nnode->pointers[node->size]->size == 0 && node->size <= T - 1\n");
            *position = node->size - 1;
            *success = 0;
            return NULL;
        }
    }
}

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