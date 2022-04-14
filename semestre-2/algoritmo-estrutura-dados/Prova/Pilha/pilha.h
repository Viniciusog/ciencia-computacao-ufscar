
typedef struct pilha Pilha;
typedef struct elemento Elemento;

Pilha *criar();
Elemento *criarElemento(char x);
int vazia(Pilha *header);
void empilha(Pilha *header, Elemento *x);
void desempilha(Pilha *header);


