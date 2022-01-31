// Feito por: Vinícius de Oliveira Guimarães

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main () {

	Pilha *s;
	s = criaPilha(s);

	empilha(s, 'H');
	empilha(s, 'A');
	empilha(s, 'O');
	empilha(s, 'F');
	empilha(s, 'K');
	empilha(s, 'W');
	empilha(s, 'C');

	printf("\nPilha normal: ");
	imprimePilha(s);

	// Inverte a pilha e em seguida mostra na tela
	inverterPilha(s);
	printf("\nPilha invertida: ");
	imprimePilha(s);

	char maiorValorAscii = maiorValorASCII(s);
	printf("\nMaior valor ASCII: %c", maiorValorAscii);

	// 1 é para retornar na ordem crescente
	ordenar(s, 1);
	printf("\nPilha ordenada (crescente): ");
	imprimePilha(s);

	ordenar(s, 0);
	printf("\nPilha ordenada (decrescente): ");
	imprimePilha(s);

	Pilha *p1;
	p1 = criaPilha();

	empilha(p1, 'A');
	empilha(p1, 'B');
	empilha(p1, 'C');

	Pilha *p2;
	p2 = criaPilha();

	empilha(p2, 'A');
	empilha(p2, 'B');
	empilha(p2, 'C');

	Pilha *p3;
	p3 = criaPilha();

	empilha(p3, 'A');
    empilha(p3, 'B');
	empilha(p3, 'C');

	printf("\nVerificar se duas pilhas são iguais: ");
	printf("\n['A', 'B', 'C'] e ['A', 'B', 'C']: %s", verificarPilhasIguais(p1, p2) == 1 ? "Iguais" : "Diferentes");
	printf("\n['A', 'B', 'C'] e ['a', 'b', 'c']: %s", verificarPilhasIguais(p1, p3) == 1 ? "Iguais" : "Diferentes");

    liberaPilha(s);
    liberaPilha(p1);
    liberaPilha(p2);
    liberaPilha(p3);

	return 0;
}
