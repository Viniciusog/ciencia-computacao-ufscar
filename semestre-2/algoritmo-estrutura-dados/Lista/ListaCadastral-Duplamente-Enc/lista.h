typedef struct node Node;

// Primitivos
Node *criar();
int vazia(Node *cabeca);
void inserir(Node * cabeca, char valor);
void remover(Node *cabeca, char valor);

// Não primitivos
void imprimir(Node *cabeca);
char maiorValorASCII(Node *cabeca);
void buscaInserir(Node *cabeca, char valor1, char valor2);
