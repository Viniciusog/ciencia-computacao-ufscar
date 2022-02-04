// Feito por: Vin�cius de Oliveira Guimar�es
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#define TAM_MAX 10

struct pilha {
	char vetor[TAM_MAX];
	int topo;
};

Pilha * criaPilha() {
	Pilha *s;
	s = (Pilha *) malloc(sizeof(Pilha));
	s->topo = 0;
	return s;
}

void empilha(Pilha *s, char x) {
	if (s->topo == TAM_MAX) {
		return;
	}
	s->vetor[s->topo] = x;
	(s->topo)++;
}

char desempilha(Pilha *s) {
	if (pilhaVazia(s)) {
		return '\0';
	}
	(s->topo)--;
	return s->vetor[s->topo];
}

int pilhaVazia(Pilha *s) {
	return s->topo <= 0;
}

int pilhaCheia(Pilha *s) {
	return s->topo == TAM_MAX;
}

Pilha * liberaPilha(Pilha *s) {
	free(s);
	return NULL;
}

// ---------- FUN��ES N�O PRIMITIVAS ----------

void inverterPilha(Pilha *s) {
	// A primeira pilha ter� os dados invertidos
	Pilha *s2;
	s2 = criaPilha();

	// Pegamos os dados de s2 e colocamos em s3. Ou seja, s3 ter� os itens da ordem
	// correta
	Pilha *s3;
	s3 = criaPilha();

	while (!pilhaVazia(s)) {
		char valor = desempilha(s);
		empilha(s2, valor);
	}

	while (!pilhaVazia(s2)) {
		char valor = desempilha(s2);
		empilha(s3, valor);
	}

	// Pegamos os dados na ordem correta que est�o dentro da pilha s3 e colocamos em s
	// Assim, s ter� os seus valores iniciais na ordem inversa
	while (!pilhaVazia(s3)) {
		char valor = desempilha(s3);
		empilha(s, valor);
	}

	liberaPilha(s2);
	liberaPilha(s3);
}


// Obs: Poderia ter sido feito apenas percorrendo o array que representa a nossa pilha
void imprimePilha(Pilha *s) {
	Pilha *s2;
	s2 = criaPilha();

	while (!pilhaVazia(s)) {
		char valor = desempilha(s);
		empilha(s2, valor);
	}

	while (!pilhaVazia(s2)) {
		char valor = desempilha(s2);
		empilha(s, valor);
		printf("%c ", valor);
	}

	liberaPilha(s2);
}

// Obs: Poderia ter sido feita apenas retornando o valor de 'Topo'
// pois ele possui o mesmo valor da quantidade de elementos na pilha
int tamanhoPilha(Pilha *s) {
	Pilha *s2;
	s2 = criaPilha();

	int tamanho = 0;

	while (!pilhaVazia(s)) {
		char valor = desempilha(s);
		empilha(s2, valor);
		tamanho++;
	}

	while(!pilhaVazia(s2)) {
		char valor = desempilha(s2);
		empilha(s, valor);
	}

	liberaPilha(s2);

	return tamanho;
}

// Pega o char que cont�m o maior valor ASCII da nossa pilha
char maiorValorASCII(Pilha *s) {
	char maiorValorASCII = 0;

	Pilha *s2;
	s2 = criaPilha();

	int cont = 0;

	while (!pilhaVazia(s)) {
		char valor = desempilha(s);
		empilha(s2, valor);

		if (cont == 0) {
			maiorValorASCII = valor;
		} else if(valor > maiorValorASCII) {
			maiorValorASCII = valor;
		}
		cont++;
	}

	while (!pilhaVazia(s2)) {
		char valor = desempilha(s2);
		empilha(s, valor);
	}

	liberaPilha(s2);

	return maiorValorASCII;
}

//Retorna o elemento do topo sem remove-lo da pilha
char consultarTopo(Pilha * s) {
	char valor = desempilha(s);
	// Se a nossa pilha estiver vazia, ent�o receberemos NULL na hora de desempilhar e portanto, eu
	// N�O posso setar NULL dentro da pilha, pois ela n�o tinha esse valor
	if (valor != '\0') {
	    empilha(s, valor);
	}
	return valor;
}

// Funciona da seguinte forma:
// Temos uma pilha auxiliar e uma vari�vel 'k' que serve para fazer a troca de elementos entre as pilhas.
// Primeiro eu pego o elemento da primeira pilha e coloco em 'k'.
// Se tiver elemento menor que 'k' dentro da pilha 2 (s2), ent�o eu tiro esses elementos da pilha 2 e coloco
// na pilha 1 (s)
// Depois, eu coloco 'k' dentro da pilha 2 caso n�o tenha mais nenhum valor menor que 'k' dentro da pilha 2.
// Repito o processo at� que a pilha 1 seja vazia
// Se tivermos os seguintes valores dentro da pilha 1: ['F', 'B', 'A', 'G'], ent�o a pilha 2 ter� o
// seguinte conjunto de n�meros: ['G', 'F', 'B', 'A']
// Logo, a �nica coisa que resta fazer � desempilhar da pilha 2 e empilhar na pilha 1
// 1 retorna a lista na ordem crescente e 0 retorna na ordem decrescente
void ordenar(Pilha *s, int crescente) {
	Pilha *s2;
	s2 = criaPilha();
	char k;

	while(!pilhaVazia(s)) {
		k = desempilha(s);

		if (pilhaVazia(s2)) {
			empilha(s2, k);
		} else {
		    char topoS2 = consultarTopo(s2);

		    while (topoS2 < k && !pilhaVazia(s2)) { // Pode colocar && topoS2 != NULL
		        char valorTopoS2 = desempilha(s2);
		        empilha(s, valorTopoS2);
		        topoS2 = consultarTopo(s2); // receber� NULL se a pilha for vazia
		    }
		    empilha(s2, k);
		}
	}

	// Se for para retornar na ordem decrescente, ent�o inverteremos a pilha 2
	if (!crescente) {
	    inverterPilha(s2);
	}

    // Aqui n�s j� teremos o valor da pilha ordenada, agora basta desempilhar de 's2' e empilhar em 's'
    while (!pilhaVazia(s2)) {
        char valor = desempilha(s2);
        empilha(s, valor);
    }

    liberaPilha(s2);
}


int verificarPilhasIguais(Pilha *s, Pilha *s2) {
    int tamanho1 = tamanhoPilha(s);
    int tamanho2 = tamanhoPilha(s2);

    if (tamanho1 != tamanho2) {
        return 0;
    }

    Pilha *aux1;
    aux1 = criaPilha();
    Pilha *aux2;
    aux2 = criaPilha();

    int igual = 1;

    while (!pilhaVazia(s)) {
        char topoS = desempilha(s);
        char topoS2 = desempilha(s2);

        empilha(aux1, topoS);
        empilha(aux2, topoS2);

        if (topoS != topoS2) {
            igual = 0;
            break;
        }
    }

    // Depois que desempilhamos das pilhas,
    // para realizar a verifica��o,
    // precisamos empilhar novamente

    while (!pilhaVazia(aux1)) {
        char valor = desempilha(aux1);
        empilha(s, valor);
    }

    while (!pilhaVazia(aux2)) {
        char valor = desempilha(aux2);
        empilha(s2, valor);
    }

    liberaPilha(aux1);
    liberaPilha(aux2);

    return igual;
}