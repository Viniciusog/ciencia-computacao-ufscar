
typedef struct nodePtr NodePtr;

NodePtr * criar();
void imprimir(NodePtr *l);
void inserir(NodePtr *l, int x);
void create(NodePtr *l);
void Remove1(NodePtr *l, int x, int *ok);
void RemoveTodos(NodePtr *l, int x, int *ok);
