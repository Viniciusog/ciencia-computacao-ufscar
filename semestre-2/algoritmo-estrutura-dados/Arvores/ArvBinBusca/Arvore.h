
typedef struct node Node;

Node *criar();
void inserir(Node **node, int valor, int *ok);
int estaNaArvore(Node *node, int valor);
Node *menorElemento(Node *node);
Node *Remove(Node **node, int valor, int *ok);
void inOrdem(Node *node);