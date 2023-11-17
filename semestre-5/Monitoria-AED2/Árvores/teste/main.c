#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Node.h"

int main() {
    Node *node = create();
    int conteudo = 6789;
    insertWrapper(&node, 1001, &conteudo);
    insertWrapper(&node, 0100, &conteudo);
    insertWrapper(&node, 0101, &conteudo);
    insertWrapper(&node, 1100, &conteudo);
    print(node);

    /* int qualDigito = 4;
    int Q = 4;
    int numero = 1024;
    for (int i = 0; i < qualDigito; i++) {
        // numero / 10^(3-0)
        // numero / 10^(3-1)
        // numero / 10^(3-2)
        // numero / 10^(3-3)
        int n = numero / pow(10, (Q-1)-i);
        printf("%d / 10^(%d-1-%d) = %d\n", numero, Q, i, n);
        printf("%d\n", n % 10);
    } */
    //printf("Apenas um teste: 102 << 10: %d", (102 << 10));
    //100110
}