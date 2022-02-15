#include <stdio.h>
#include <stdlib.h>

#include "TadPilha.c"

int main() {
    Node * cabeca;
    cabeca = create();


    push(cabeca, 'B');
    push(cabeca, 'D');
    push(cabeca, 'F');
    push(cabeca, 'B');
    push(cabeca, 'O');

    printf("Próximo conteúdo: %c", cabeca->proximo->conteudo);

    printf("\nPilha: ");
    print(cabeca);

    printf("\nTamanho da pilha: ");
    printf("%d", size(cabeca));
}