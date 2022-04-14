#include <stdio.h>
#include <stdlib.h>
#include "tadLista.c"

int main() {
    Lista *l1 = criar();
    int ok;
    insere(l1, 1, &ok);
    insere(l1, 2, &ok);
    insere(l1, 3, &ok);
    Lista *l2 = criar();
    insere(l2, 2, &ok);
    insere(l2, 3, &ok);
    insere(l2, 4, &ok);
    insere(l2, 5, &ok);

    printf("%d", nroPessoasVacinadasOuInfectadas(l1, l2));
}