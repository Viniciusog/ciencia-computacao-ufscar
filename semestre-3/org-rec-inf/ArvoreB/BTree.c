
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

int removeWrapper(Node *node, int key) {
    int index;
    while (index < node->size && node->keys[index] < key) {
        index++;
    }

    if (node->isLeaf) {
        if (node->keys[index] == key){
            // ajustar chaves
            for (int i = index; i < node->size - 1; i++)     {
                node->keys[i] = node->keys[i + 1];
            }
            return 1;
        } else {
            return 0;
        }
    } else {
        if (node->keys[index] == key) {
            // pegar a maior chave da subárvore esquerda e colocar na posicao index
            // se não tiver como, tentar pegar a menor chave da subárvore da direita
            // se também não tiver como, então teremos que realizar o merge

        } else {
            // Se tivermos que remover de um sub nó
            // precisamos após remover do sub nó, verificar se ele continua mantendo o tamanho > T - 1
            int success = removeNode(node, index, node->pointers[index], key);
            if (node->pointers[index]->size < T - 1) { 
                // todo: criar função para pegar elemento emprestado de nós internos,
                // todo: ou seja, realizar rotação direita e esquerda com nós internos
                // todo: lembrar de controlar os ponteiros
                // Teremos que arrumar o nó para ter pelo menos T - 1 elementos
                if (index == 0 && node->pointers[index + 1]->size > T - 1) {
                    // pegar emprestado do nó na direita
                } else if (index == 0 && node->pointers[index + 1]->size <= T - 1) {
                    // realizar merge do nó da direita no nó atual
                } else if (index == 2*T && node->pointers[index - 1]->size > T - 1) {
                    // pegar emprestado do nó na esquerda
                } else if (index == 2*T && node->pointers[index - 1]->size <= T - 1) {
                    // realizar merge do nó atual no nó da esquerda
                }
            }
            return success;
        }
    }
}

int removeNode(Node *parent, int position, Node *node, int key) {
    int index = 0 ;
    while (index < node->size && node->keys[index] < key) {
        index++;
    }
    
    if (node->keys[index] == key) {
        if (node->isLeaf && node->size > T - 1) {
            // remover normalmente
            // tem que ser menor do que size - 1, pois se o nó estiver completamente cheio
            // se for menor do que size, então na última posição estaríamos pegando da posicao [size] que não existe
            for (int i = index; i < node->size - 1; i++) {
                node->keys[i] = node->keys[i + 1];
            }
            node->size--;
        } else if (node->isLeaf && node->size <= T - 1) {
            if (position == 0) {
                // verificar apenas na direita
                Node * rightBrother = parent->pointers[position + 1];

                if (rightBrother->size > T - 1) {
                    leftRotationLeaf(parent, position, node);
                    // mandar remover a chave apartir do nó atual
                    // observe que será o nosso pai que deverá nos corrigir caso tivermos size <= T - 1
                    return removeNode(parent, position, node, key);
                } else {
                    mergeLeaf(parent, position, node, 0);
                    // em seguida, mandar remover a partir do nó atual, a chave que queremos
                    // observe que ao retornar a remoção apartir do nosso nó atual, é o nosso pai
                    // que irá precisar nos corrigir caso após o merge ficarmos com size <= T - 1
                    return removeNode(parent, position, node, key);
                }
            } else if (position = 2*T) {
                // verificar apenas na esquerda
                Node *leftBrother = parent->pointers[position - 1];

                if (leftBrother->size > T - 1) {
                    rightRotationLeaf(parent, position, node);
                    // correção caso tivermos size <= T - 1 será feita pelo nosso pai
                    return removeNode(parent, position, node, key);
                } else {
                    mergeLeaf(parent, position, node, 1);
                    // o nosso pai que terá que verificar se ainda continuamos com tamanho > T - 1 e realizar as
                    // arrumações necessárias caso não tivermos com tamanho > T - 1
                    return removeNode(parent, position, node, key);
                }
            } else {
                // verifica se tem como pegar emprestado do irmão da direita ou da esquerda
                // se não tiver como nenhuma das opções, então realizar o merge
                Node *rightBrother = parent->pointers[position + 1];
                Node *leftBrother = parent->pointers[position - 1];

                if (rightBrother->size > T - 1) {
                    leftRotationLeaf(parent, position, node);
                    // nosso pai irá precisar verificar se continuamos a ter tamanho > T - 1
                    return removeNode(parent, position, node, key);
                } else if (leftBrother->size > T - 1) {
                    rightRotationLeaf(parent, position, node);
                    // nosso pai irá precisar verificar se continuamos a ter tamanho > T - 1
                    return removeNode(parent, position, node, key);
                } else {
                    mergeLeaf(parent, position, node, 0);
                    // nosso pai irá precisar verificar se continuamos a ter tamanho > T - 1
                    return removeNode(parent, position, node, key);
                }
            }
        } else if (!node->isLeaf && node->size > T - 1) {
            // todo: verificar a remoção de nó interno com size > T - 1

        } else if (!node->isLeaf && node->size <= T - 1) {
            // todo: vai ter que fazer aqueles processos de rotação ou merge com nós internos
        }
    } else {
        if (node->isLeaf) {
            return 0;
        } else {
            int sucess = removeNode(node, index, node->pointers[index], key);
            // todo: fazer a verificação se o nó alterado (node->pointers[index]) continua com tamanho > T-1
            // todo: sem não tiver size > T - 1, então precisa realizar as configurações para arrumar
            return sucess;
            // obs, ao retornar da remoção, precisamos verificar se o nó continuar tendo tamanho maior do que
            // T - 1, e se não tiver, precisaremos arrumar a estrutura.

        }
    }
}

void mergeLeaf(Node *parent, int position, Node *node, int withLeftNode) {
    Node *rightBrother = parent->pointers[position + 1];
    Node *leftBrother = parent->pointers[position - 1];
    Node *myNode = node;

    int keyFromParent = parent->keys[position];
    
    if (withLeftNode) {
        myNode = leftBrother;
        rightBrother = node;
        keyFromParent = parent->keys[position - 1];
        position--;
    }

    // realizar o merge do nó atual com o nó da direita
    
    myNode->keys[myNode->size] = keyFromParent;
    myNode->size++;
    for (int i = 0; i < rightBrother->size; i++) {
        myNode->keys[myNode->size + i] = rightBrother->keys[i];
    }
    myNode->size += rightBrother->size;
    rightBrother->size = 0;
    // arrumando as chaves do pai
    for (int i = position; i < parent->size - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
    }
    // arrumando os ponteiros do pai
    for (int i = position + 1; i < parent->size; i++) {
        parent->pointers[i] = parent->pointers[i + 1];
    }
    parent->size--;
}

void leftRotationLeaf(Node *parent, int position, Node *node) {
    Node * rightBrother = parent->pointers[position + 1];

    if (rightBrother->size > T - 1) {
        // tem como pegar emprestado
        int keyFromParent = parent->keys[position];
        node->keys[node->size] = keyFromParent;
        node->size++;
        parent->keys[position] = rightBrother->keys[0];
        // arrumar as chaves do irmão da direita
        for (int i = 0; i < rightBrother->size - 1; i++) {
            rightBrother->keys[i] = rightBrother->keys[i + 1];
        }
        rightBrother->size--;
    }
}

void rightRotationLeaf(Node *parent, int position, Node *node) {
    Node *leftBrother = parent->pointers[position - 1];

    if (leftBrother->size > T - 1) {
        // pegar emprestado da esquerda
        int keyFromParent = parent->keys[position - 1];
        insertIncompleteNode(node, keyFromParent);
        parent->keys[position - 1] = leftBrother->keys[leftBrother->size - 1];
        leftBrother->size--;
    }
}

void mergeInternalNode(Node *parent, int position, Node *node, int withLeftNode) {
    if (withLeftNode) {
        Node *leftBrother = parent->pointers[position - 1];

        int keyFromParent = parent->keys[position];
        leftBrother->keys[leftBrother->size] = keyFromParent;
        leftBrother->size++;

        // passar as chaves do nó para o irmão da esquerda
        for (int i = 0; i < node->size; i++) {
            leftBrother->keys[leftBrother->size + i] = node->keys[i];
        }

        // passar os ponteiros do nó para o irmão da esquerda
        for (int i = 0; i <= node->size; i++) {
            leftBrother->pointers[leftBrother->size + i] = node->pointers[i];
        }

        leftBrother->size += node->size;
        node->size = 0;

        // arrumar as chaves do pai, começa em position - 1, pois realizamos o merge no nó da esquerda
        for (int i = position - 1; i < parent->size - 1; i++) {
            parent->keys[i] = parent->keys[i + 1];
        }

        // arrumar ponteiros do pai
        for (int i = position; i < parent->size; i++) {
            parent->pointers[i] = parent->pointers[i + 1];
        }
        parent->size--;
    } else {
        // merge com o nó da direita
        Node *rightBrother = parent->pointers[position + 1];
        int keyFromParent = parent->keys[position];

        node->keys[node->size] = keyFromParent;
        node->size++;

        // passa as chaves do nó da direita para o nosso nó
        for (int i = 0; i < rightBrother->size; i++) {
            node->keys[node->size + i] = rightBrother->keys[i];
        }

        // passa os ponteiros do nó da direita para o nosso nó
        for (int i = 0; i <= rightBrother->size; i++) {
            node->pointers[node->size + i] = rightBrother->keys[i];
        }
        node->size+= rightBrother->size;
        rightBrother->size = 0;
        
        // arrumar as chaves do pai
        for (int i = position; i < parent->size - 1; i++) {
            parent->keys[i] = parent->keys[i + 1];
        }

        // arrumar os ponteiros do pai;
        for (int i = position + 1; i < parent->size; i++) {
            parent->pointers[i] = parent->pointers[i + 1];
        }
        parent->size--;
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

/*
int remove(Node *node, int key) {
    int index = 0;
    while (index < node->size && node->keys[index] < key) {
        index++;
    }

    if (node->isLeaf) {
        if (node->keys[index] == key) {
            for (int i = index; i < node->size; i++) {
                node->keys[i] = node->keys[i + 1];
            }
            node->size--;
            return 1;
        } else {
            return 0;
        }
    } else {
        // Fazendo aqui o caso de remoção se a chave estiver em nó folha (Falta a parte da chave estando em nó interno)
        Node *subNode = node->pointers[index];

        // ao invés de percorrer o subnó verificando se a chave está lá,
        // // podemos verificar se o subnó é uma folha e 
        int isInSubNode = 0;
        for (int i = 0; i < subNode->size; i++) {
            if (subNode->keys[i] == key) {
                isInSubNode = 1;
                break;
            }
        }

        if (!isInSubNode && !subNode->isLeaf) {
            int success = remove(subNode, key);
            // arrumar nó no retorno da chamada recursiva caso fique com size <= T-1
            return success;
        } else if (!isInSubNode && subNode->isLeaf){
            return 0;
        }

        // só podemos realizar esse if se soubermos que a chave está dentro do nó
        if (subNode->size > T-1 ) {
            int success = remove(subNode, key);
            // aqui iremos precisar verificar se o subnó após a remoção continua tendo size > T - 1 e
            // fazer as alterações caso não tenha
            // isso é, no retorno da chamda recursiva
        } else {
            // verificar se irmão da esquerda (e direita) do subnó possui chave para emprestar (size > T - 1)
            // se tiver, fazer as alterações necessárias
            // em seguida chamar para fazer a remoção diretamente do sub nó
            // lembrar de retornar a chamda

            // Se não tiver, fazer merge com o irmão esquerdo ou direito
            // em seguida chamar função para remover chave a partir do nó gerado pelo merge, pois sabemos que 
            // esse nó agora terá 2T - 1 chaves
        }
    }
}*/