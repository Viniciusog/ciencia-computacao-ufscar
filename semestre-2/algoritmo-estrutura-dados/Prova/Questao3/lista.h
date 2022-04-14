typedef struct pessoa Pessoa;
typedef struct lista Lista;

Lista *criar();
int vazia(Lista *lista);
void insere(Lista *lista, int valor, int *ok);
void remover(Lista *lista, int valor, int *ok);
void imprimir(Lista *lista);
int estaNaLista(Lista *lista, int valor);
void pegaOPrimeiro(Lista *lista, Pessoa **pessoa);
void pegaOProximo(Lista *lista, Pessoa **pessoa, int *temElemento);
int nroPessoasVacinadasOuInfectadas(Lista *l1, Lista *l2);

