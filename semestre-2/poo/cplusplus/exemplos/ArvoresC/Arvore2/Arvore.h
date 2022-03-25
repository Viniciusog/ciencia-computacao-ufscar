typedef struct node Node;

Node *criar();
void inserir(Node **a, int valor);
Node *remover(Node **a, int valor);
void inOrdem(Node **a);
int vazia(Node **a);
int altura(Node **a);
void destroi(Node **a);
int esta_na_arvore(Node **a, int valor);
Node *pegarMaiorElemento(Node **a);
Node *pegarMenorElemento(Node **a);
Node *pegarElemento(Node **a, int valor, int *ok);