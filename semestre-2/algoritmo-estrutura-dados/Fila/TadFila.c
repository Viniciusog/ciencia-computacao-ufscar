// Vinícius de Oliveira Guimarães
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "TadPilha.c"

#define TAM_MAX 10

#define VAZIA 0
#define CHEIA 1
#define NORMAL 2

struct fila {
    int inicio;
    int proximo;
    char vetor[TAM_MAX];
    int estado; // 0 vazia, 1 cheia, 2 tem espaço sobrando
};

Fila * criarFila() {
    Fila *f;
	f = (Fila *) malloc(sizeof(Fila));
	f->inicio = 0;
    f->proximo = 0; // Representa a primeira posição vazia que poderemos colocar valores dentro
    f->estado = 0;
    return f;
}

/* 
DEFINIÇÕES
Fila cheia: Uma fila está cheia se a posição "próximo" chega na posição "início"
    - Só podemos sair do estado "cheia" se remover um item da fila
Fila vazia: Uma fila está vazia se a posição "início" chega na posição "próximo"
    - Só podemos sair do estado "vazia" se adicionar um item na fila

A fila é circular, ou seja, quando a posição "início" ou a posição "próximo" 
for igual a TAM_MAX - 1, passaremos para a posição 0.
*/

void inserirNaFila(Fila *f, char valor) {
    // Se a fila estiver cheia, apenas retorna
    if (f->estado == CHEIA) {
        printf("Erro! Fila está cheia!");
        return;
    }

    f->vetor[f->proximo] = valor;

    // Controlar fila rotatória
    if (f->proximo == TAM_MAX - 1) {
        f->proximo = 0;
    } else {
        (f->proximo)++;
    }

    // Se depois de mudar a posição do próximo tivermos próximo igual ao início, então sabemos que a fila está cheia
    // O estado só sairá de 1 (cheia) quando removermos algum item da fila
    if (f->proximo == f->inicio) {
        f->estado = CHEIA;
    } else {
        // Se a fila estiver vazia anteriormente e inserirmos um valor na fila, temos que mudar de VAZIA para NORMAL
        f->estado = NORMAL;
    }
}

char removerDaFila(Fila *f) {
    // Se a fila estiver vazia 
    if (f->estado == VAZIA) {
        printf("Erro! Fila está vazia!\n");
        return '\0';
    }
    char valor = f->vetor[f->inicio];

    if (f->inicio == TAM_MAX - 1) {
        f->inicio = 0;
    } else {
        f->inicio++;
    }

    // Se ao incrementarmos o 'inicio', tivermos início sendo igual ao próximo, então 
    // sabemos que a fila está vazia
    if (f->inicio == f->proximo) {
        f->estado = VAZIA;
    } else {
        // Precisamos mudar o estado para 2 pois caso estivessemos com fila cheia, quando removermos algum valor, temos 
        // que sair da fila cheia e dizer que existe espaço sobrando.
        // Precisamos mudar o estado para 2, pois se início e próximo forem iguais anteriormente o valor continuaria sendo 1 (fila cheia)
        f->estado = NORMAL;
    } 
    return valor;
}

void liberarFila(Fila *f) {
    free(f);
}

// Remove os itens da fila principal, adiciona na fila auxiliar e imprime na tela
// Em seguida, insere os itens de volta na fila principal
void imprimirFila(Fila *f) {
    Fila * aux;
    aux = criarFila();

    while(f->estado != VAZIA) {
        char valor = removerDaFila(f);
        printf("%c ", valor);
        inserirNaFila(aux, valor);
    }

    while (aux->estado != VAZIA) {
        char valor = removerDaFila(aux);
        inserirNaFila(f, valor);
    }

    liberarFila(aux);
}

// Remove os itens da fila principal, adiciona na fila auxiliar e conta a quantidade de itens
// Em seguida, insere os itens de volta na fila principal
int tamanhoFila(Fila *f) {
    Fila *aux;
    aux = criarFila();

    int qtd = 0;

    while (f->estado != VAZIA) {
        char valor = removerDaFila(f);
        qtd++;
        inserirNaFila(aux, valor);
    }

    while (aux->estado != VAZIA) {
        char valor = removerDaFila(aux);
        inserirNaFila(f, valor);
    }

    liberarFila(aux);
    return qtd;
}


// Este método não é muito eficiente, pois como estamos usando ponteiros de filas estou
// removendo todos os elementos das duas filas e adicionando nas auxiliares.
// Em seguida, removemos todos os elementos das filas auxiliares e colocamos dentro das filas originais
// Ou seja, mesmo que o primeiro elemento das duas filas forem diferentes, eu estarei removendo tudo e adicionando tudo.
// (Resumindo, não consigo usar break; com ponteiros de filas sem realizar algum cálculo para cada elemento removido das filas)
int verificarFilasIguais(Fila * f1, Fila * f2) {
    if (tamanhoFila(f1) != tamanhoFila(f2)) return 0;

    Fila *aux1;
    aux1 = criarFila();

    Fila *aux2;
    aux2 = criarFila();

    int igual = 1;

    // Compara os elementos das duas filas
    while (f1->estado != VAZIA) {
        char v1 = removerDaFila(f1);
        char v2 = removerDaFila(f2);

        if (v1 != v2) igual = 0;

        inserirNaFila(aux1, v1);
        inserirNaFila(aux2, v2);
    }
    
    // Insere de volta nas filas originais os elementos que estão nas filas auxiliares
    while (aux1->estado != VAZIA) {
        char valorAux1 = removerDaFila(aux1);
        char valorAux2 = removerDaFila(aux2);
        inserirNaFila(f1, valorAux1);
        inserirNaFila(f2, valorAux2);
    }

    return igual;
}

// Ordenação de fila com pilha auxiliar.
// Foi feita a importação dos códigos de TadPilha criados na atividade anterior.
void ordenarFila(Fila * f, int crescente) {
    int tamanhoFilaF = tamanhoFila(f);
    Fila *fAux;
    fAux = criarFila();
 
    Pilha *pAux;
    pAux = criaPilha();

    // Pode ser que somente estar cheia não é sinônimo de resolução. Verificar se a fila auxiliar também precisa estar vazia
    while (tamanhoPilha(pAux) != tamanhoFilaF) {

        char elementoFila;
        // Se a nossa fila principal estiver vazia, então o elemento será pego da fila auxiliar
        // O elemento atual da comparação só será pego da fila principal caso ela não for vazia
        if (f->estado != VAZIA) {
            elementoFila = removerDaFila(f);
        } else if (fAux->estado != VAZIA) {
            elementoFila = removerDaFila(fAux);
        }

        // Se a pilha for vazia, então pega o primeiro valor da fila e coloca na pilha
        if (tamanhoPilha(pAux) == 0) {
            empilha(pAux, elementoFila);
        } else {

            char topoPilhaAux = consultarTopo(pAux);

            while (topoPilhaAux > elementoFila && !pilhaVazia(pAux)) { // se a pilha estiver vazia irá retornar \0.
                topoPilhaAux = desempilha(pAux);
                inserirNaFila(fAux, topoPilhaAux);
                topoPilhaAux = consultarTopo(pAux);
            }

            // Depois que tiver retirado os elementos maiores do que o 1º elemento da fila principal da pilha auxiliar, 
            // iremos colocar esse 1º elemento da fila principal dentro da pilha auxiliar
            empilha(pAux, elementoFila);

            // Quando formos retirar da fila auxiliar, precisaremos remover da pilha auxiliar todos os elementos maiores
            // do que o elemento atual (1º elemento da fila auxiliar) e em seguida coloca-los dentro da fila auxiliar.
            while (fAux->estado != VAZIA) {

                char valorFilaAux = removerDaFila(fAux); //1º elemento da fila
                topoPilhaAux = consultarTopo(pAux);

                while (topoPilhaAux > valorFilaAux && !pilhaVazia(pAux)) { // remover da pilha os valores maiores que valorFilaAux
                    topoPilhaAux = desempilha(pAux);
                    inserirNaFila(fAux, topoPilhaAux);
                    topoPilhaAux = consultarTopo(pAux);
                }

                empilha(pAux, valorFilaAux);
            }
        }
    }

    // Quando chegarmos aqui, a pilha estará com os valores ORDENADOS da fila.
    // Os elementos na pilha estarão do menor para o maior (Valores crescentes da base até o topo)

    // Se crescente for 1, então precisamos inverter a pilha para inserir os valores na ordem correta na fila
    if (crescente) {
        inverterPilha(pAux);
    }

    while (!pilhaVazia(pAux)) {
        char topoPilhaAux = desempilha(pAux);
        inserirNaFila(f, topoPilhaAux);
    }

    liberaPilha(pAux);
    liberarFila(fAux);
}