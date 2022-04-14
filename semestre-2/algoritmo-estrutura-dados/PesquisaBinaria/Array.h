
typedef struct array Array;

Array *criar();
void imprimir(Array*a);
int buscaSequencial(Array *a, int valor);
int buscaBinaria(Array *a, int e, int d, int valor);
// Executar esta função para que a busca binária aconteça
int executarBuscaBinaria(Array *a, int valor);