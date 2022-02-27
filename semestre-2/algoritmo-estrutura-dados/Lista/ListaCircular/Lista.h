typedef struct node Node;

Node *criarLista();
void inserir(Node *lista, char valor);
char remover(Node *lista);
void imprimir(Node *n);

//retorna ponteiro para primeiro elemento encontrado por valor
Node *buscar(Node *cabeca, char valor); 

//retorna ponteiro para elemento encontrado por índice
Node *selecionar(Node *cabeca, int posicao); 

//Insere item antes do primeiro elemento encontrado com determinado valor.
//valor1: para encontrar o elemento
//valor2: conteúdo do novo item
void buscaInsere(Node *cabeca, char valor1, char valor2);

// Remove o primeiro elemento encontrado por valor.
void buscaRemove(Node *cabeca, char valor);