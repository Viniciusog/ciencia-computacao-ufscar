typedef struct node Node;

Node *create();
Node *insert(Node *tree, int key, int valor);
Node *insertAVL(Node *tree, int key, int valor, int *heightIncreased);
Node *removeFromTree(Node **tree, int valor, int *heightDecreased);
void inOrder(Node *tree);
void print(Node *tree);
Node *getNodeHighestValue(Node *tree);
Node *rightRotation(Node *tree);
Node *leftRotation(Node *tree);
Node *leftRightRotation(Node *tree);
Node *rightLeftRotation(Node *tree);