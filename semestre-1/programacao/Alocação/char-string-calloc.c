#include <stdio.h>
#include <stdlib.h>


int main()
{
    // Meu nome é um ponteiro que aponta para um array de char
    char * nome;
    // meu nome irá apontar para um espaço em memória que corresponde ao tamanho de 10 chars
    nome = (char *) calloc(10, sizeof(char));
    
    printf("INSIRA O SEU NOME: \n");
    gets(nome);
    printf("SEU NOME: %s", nome);
    return 0;
}
