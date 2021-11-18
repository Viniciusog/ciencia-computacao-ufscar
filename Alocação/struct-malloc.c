/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cadastro {
      char nome[50];
      int idade;
};

int main()
{
    //Meu sCad é um ponteiro que aponta para um array de 'struct cadastro'
    struct cadastro * vCad;
    vCad = (struct cadastro *) malloc(3 * sizeof(struct cadastro));
    strcpy(vCad[0].nome, "Fernando");
    vCad[0].idade = 18;
    strcpy(vCad[1].nome,"Maria");
    vCad[1].idade = 25;
    strcpy(vCad[2].nome, "Rogério");
    vCad[2].idade = 36;
    
    for (int i = 0; i < 3; i++) {
       printf("\nNome: %s", vCad[i].nome);
       printf("\nIdade %d", vCad[i].idade);
    }
    
    free(vCad);
    return 0;
}
