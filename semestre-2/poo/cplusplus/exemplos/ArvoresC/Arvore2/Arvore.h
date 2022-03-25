typedef struct node Node;

typedef Node *Arvore;

/* Arvore inserir(Arvore arvore, int valor);
 */

void inserir(Node **a, int valor);
void inOrdem(Node **a);
int vazia(Node **a);