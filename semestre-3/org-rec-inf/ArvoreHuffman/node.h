
typedef struct node Node;
typedef struct nodeTree NodeTree;
typedef struct text Text;

typedef struct text {
    int quantity;
    void *content;
} Text;

typedef struct nodeTree {
    int key; // quantidade de uma palavra
    void *content; // ponteiro de tipo qualquer que aponta para o conteúdo
    NodeTree *left;
    NodeTree *right;
} NodeTree;

typedef struct node {
    Node *next;
    Node *previous;
    NodeTree *tree; // para manter a ordem, iremos ordenar pela tree->key
} Node;

Node *create();
void insert(Node **node, Text t, NodeTree *tree);
Node *removeMin(Node **node);
NodeTree *generateHuffmanTree(Node **node);
void print(Node *node);
void printTree(NodeTree *tree);