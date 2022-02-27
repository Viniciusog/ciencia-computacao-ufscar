 
 #include <stdio.h>
 #include <stdlib.h>
 #include "lista.h"

 int main() {

    Node *cabeca;
    cabeca = criar();

    inserir(cabeca, 'H');

    buscaInsere(cabeca, 'U', 'L');
    
    //printf("\n");
    imprimir(cabeca);

    /* inserir(cabeca, 'H');
    inserir(cabeca, 'I');
    inserir(cabeca, 'A');
    inserir(cabeca, 'D');
    inserir(cabeca, 'B');

    imprimir(cabeca); //B D A I H 

    remover(cabeca); 

    printf("\n");
    imprimir(cabeca); //D A I H 

    buscaInsere(cabeca, 'A', 'P');

    printf("\n");
    imprimir(cabeca); //D P A I H 

    buscaRemove(cabeca, 'I');
    
    printf("\n");
    imprimir(cabeca); //D P A H  */
 }
