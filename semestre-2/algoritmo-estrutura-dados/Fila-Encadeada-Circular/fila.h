typedef struct fila Fila;
typedef struct node Node;

Fila *criar();
void inserir(Fila *fila, char valor);
char remover(Fila *fila);
void imprimir(Fila *fila);
void destruir(Fila *fila);
