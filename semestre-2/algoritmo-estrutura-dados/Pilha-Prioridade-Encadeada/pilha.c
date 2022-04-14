typedef struct pilha Pilha;
typedef struct node Node;

Pilha *criar();
void inserir(Pilha *pilha, char valor);
char remover(Pilha *pilha);
void imprimir();