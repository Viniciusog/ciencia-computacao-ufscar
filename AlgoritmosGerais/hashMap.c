#include <stdio.h>
#include <string.h>
//strcpy(a[i].chave, "Olá");

#define N 5

typedef struct hashMap {
    double valor;
    char chave[30];
} HashMap;

void lerValoresHashMap(HashMap a[N]) {
    int i;
    for (i = 0; i < N; i++) {
        scanf("%s %lf", a[i].chave, &a[i].valor);
    }
}

void printarValoresHashMap(HashMap a[N]) {
    int i;
    printf("\n[\n");
    for (i = 0; i< N; i++) {
        printf(" {\n");
        printf("  Chave: %s,\n", a[i].chave);
        printf("  Valor: %lf,\n", a[i].valor);
        printf(" }");
        if (i != N - 1) {
            printf(",\n");
        }
    }
    printf("\n]\n");
}

double pegarValorPorChave(HashMap a[N], char chave[N]) {
    int i;
    for (i = 0; i < N; i++) {
        if (strcmp(a[i].chave, chave) == 0) {
            return a[i].valor;
        }
    } 
}


int main(int argc, char const *argv[])
{
    HashMap myHashMap[N];
    
    lerValoresHashMap(myHashMap);
    printarValoresHashMap(myHashMap);

    // Nesse caso só irá funcionar caso eu tenha adicionado uma chave uva
    double valor = pegarValorPorChave(myHashMap, "Uva");
    printf("\n O valor encontrado com a chave 'Uva' é: %lf", valor);

    return 0;
}