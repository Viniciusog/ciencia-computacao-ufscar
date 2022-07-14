typedef struct node {
    char *palavra;
    int tam;
} Node;

void inserir(Node **arvore, char *palavra) {
    if ((*arvore) == NULL) {
        Node *newNode = (Node *) malloc(sizeof(Node));
        newNode->palavra = palavra;
        newNode->tam = sizeof(palavra) / sizeof(palavra[0]);

    }

}