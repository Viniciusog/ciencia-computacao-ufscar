
typedef struct fila Fila;
typedef struct node Node;

Fila *criar();
void inserir(Fila *fila, int idade);
int remover(Fila *fila);
void imprimir(Fila *fila);