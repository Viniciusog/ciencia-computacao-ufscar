typedef struct node Node;

Node *criar();
int vazia(Node *cabeca);
void inserir(Node * cabeca, char valor);
char remover(Node *cabeca);
void imprimir(Node *cabeca);
void buscaInsere(Node *cabeca, char valor1, char valor2);
void buscaRemove(Node *cabeca, char valor);