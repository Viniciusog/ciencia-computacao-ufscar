
typedef struct fila Fila;

//Funções primitivas
Fila * criarFila();
void inserirNaFila(Fila *f, char valor);
char removerDaFila(Fila *f);
void liberarFila(Fila *f);

// Funções não primitivas
void imprimirFila(Fila *f);
int tamanhoFila(Fila *f);
int verificarFilasIguais(Fila * f1, Fila * f2);
void ordenarFila(Fila *f, int crescente); // 1 = crescente, 0 = decrescente