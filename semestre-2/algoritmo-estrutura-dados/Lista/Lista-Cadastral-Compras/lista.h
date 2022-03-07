typedef struct elemento Elemento;
typedef struct lista Lista;

Lista *criar();

void primeiroElemento(Lista *lista, Elemento **elemento);
int vazia(Lista *lista);
//Se a inserção ocorreu corretamente, então ok será 1
void inserir(Lista *lista, char valor, int *ok);
//Remove da lista o elemento de conteúdo igual a valor. 
//Se o elemento existir dentro da lista, então ok será 1, senão, ok será 0
void remover(Lista *lista, char valor, int *ok);
int estaNaLista(Lista *lista, char valor);
//Vai pegar o primeiro elemento da 
void pegaOPrimeiro(Lista *lista, Elemento **elemento);
void pegaOProximo(Lista *lista, Elemento **elemento, int *temElemento);
//Retorna o valor do próximo elemento da Lista, em relação à última chamada à uma das operações PegaOPrimeiro ou PegaOPróximo. 
//Para isso, iremos gravar na lista, um ponteiro que aponta para o nó atual, para poder controlar quem é o próximo elemento a ser pego.
int itensCompradosErroneamente(Lista *carrinhoCompras, Lista *listaCompras);

