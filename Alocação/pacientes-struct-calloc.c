/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct pessoa
{
  char nome[50];
  int idade;
  float peso;
  float altura;
}

main ()
{

  struct pessoa *pessoasAtendidas;
  int qtdPessoas;

  printf ("Insira a quantidade de pessoas a serem cadastradas: ");
  scanf ("%d", &qtdPessoas);

  pessoasAtendidas =
    (struct pessoa *) calloc (qtdPessoas, sizeof (struct pessoa));

  for (int i = 0; i < qtdPessoas; i++)
    {
      printf ("%dº: Pessoa\n", (i + 1));
      printf ("Nome: \n");
      scanf ("%s", pessoasAtendidas[i].nome);
      printf ("Idade:\n");
      scanf ("%d", &pessoasAtendidas[i].idade);
      printf ("Peso: \n");
      scanf("%f", &pessoasAtendidas[i].peso);
      printf ("Altura: \n");
      scanf ("%f", &pessoasAtendidas[i].altura);
    }
    
    
    for (int i = 0; i < qtdPessoas; i++)
    {
      printf("\n");
      printf ("%dº: Pessoa\n", (i + 1));
      printf ("Nome: %s\n", pessoasAtendidas[i].nome);
      printf ("Idade: %d\n", pessoasAtendidas[i].idade);
      printf ("Peso: %f\n", pessoasAtendidas[i].peso);
      printf ("Altura: %f\n", pessoasAtendidas[i].altura);

    }
}
