typedef struct node Node;

Node *create();
Node * push(Node *cabeca, char valor);
char pop(Node * cabeca);

int isEmpty(Node *cabeca);
int size(Node *cabeca);
void print(Node * cabeca);