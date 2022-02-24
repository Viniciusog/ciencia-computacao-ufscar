typedef struct node Node;

// Métodos primitivos de uma lista cadastral
Node * criar();
Node * inserir(Node *cabeca, char valor);
char remover(Node *cabeca, char valor);
int vazia(Node * cabeca);

// Métodos não primitivos de uma lista cadastral
void imprimir(Node *cabeca);
int tamanho(Node *cabeca);
void destruir(Node *cabeca);
Node * copiar(Node *cabeca);
int estaNaLista(Node *cabeca, char valor);
Node * juntarListas(Node *cabeca1, Node *cabeca2);
Node * interseccao(Node *cabeca1, Node *cabeca2);
int saoIguais(Node *cabeca1, Node *cabeca2);