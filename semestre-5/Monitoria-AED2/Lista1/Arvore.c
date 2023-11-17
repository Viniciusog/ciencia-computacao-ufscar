#include "Arvore.h"
#include "Fila.h"

Noh *criarArvore() {
    return NULL;
}

Noh * novoNoh(int valor) {
    Noh *novo = (Noh *) malloc(sizeof(Noh));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
    novo->valor = valor;
    return novo;
}

void inserir(Noh **arvore, int elemento) {
    if ((*arvore) == NULL) {
        *arvore = novoNoh(elemento);
    } else if (elemento <= (*arvore)->valor){
        inserir(&(*arvore)->esq, elemento);
    } else {
        // elemento > (*arvore)->valor
        inserir(&(*arvore)->dir, elemento);
    }
}

// Como depende da quantidade de elementos, então é O(n)
int calcularAltura(Noh *arvore) {
    if (arvore == NULL) {
        return -1;
    }
    int alturaEsquerda = calcularAltura(arvore->esq);
    int alturaDireita = calcularAltura(arvore->dir);
    if (alturaEsquerda > alturaDireita) {
        return alturaEsquerda + 1;
    }
    return alturaDireita + 1;
}

int calcularAlturaIterativamente(Noh *arvore) {
    if (arvore == NULL) {
        return -1;
    }

    int altura = 0;
    // Função chamada do arquivo Fila.h
    Fila *fila = criarFila();
    inserirNaFila(fila, arvore);

    while (fila->tam > 0) {
        int quantidadeNaFila = fila->tam;
        int temFilho = 0;
        for (int i = 0; i < quantidadeNaFila; i++) {
            Node *primeiroNohFila = removerPrimeiroDaFila(fila);
            if (primeiroNohFila->conteudo->esq != NULL) {
                temFilho = 1;
                inserirNaFila(fila, primeiroNohFila->conteudo->esq);
            }
            if (primeiroNohFila->conteudo->dir != NULL) {
                temFilho = 1;
                inserirNaFila(fila, primeiroNohFila->conteudo->dir);
            }
            // Observe que quando fazemos free no nó (node) da 
            // lista, não estamos fazendo free no seu conteúdo.
            free(primeiroNohFila);
        }
        // Se algum dos nós do nível (altura) atual tem filho.
        if (temFilho == 1) {
            altura++;
        }
    }
    free(fila);
    return altura;
}

void imprimirArvoreInOrder(Noh *arvore) {
    if (arvore == NULL) {
        return;
    }
    imprimirArvoreInOrder(arvore->esq);
    if (arvore->esq == NULL && arvore->dir == NULL) {
        printf("%d ", arvore->valor);
    }    
    imprimirArvoreInOrder(arvore->dir);
}

int calcularQuantidadeNos(Noh *arvore) {
    int qtd = 0;
    calcularQuantidadeNosInterno(arvore, &qtd);
    return qtd;
}

void calcularQuantidadeNosInterno(Noh *arvore, int *pQtd) {
    if (arvore == NULL)  {
        return;
    }
    (*pQtd)++;
    calcularQuantidadeNosInterno(arvore->esq, pQtd);
    calcularQuantidadeNosInterno(arvore->dir, pQtd);
}

// Essa função serve apenas como um wrapper (Embrulho) da função
// que realmente irá realizar o trabalho sujo.
void preencherPai(Noh *arvore) {
    preencherPaiInterno(arvore, NULL);
}

// Como depende da quantidade de nós da árvore, então é O(n)
void preencherPaiInterno(Noh *arvore, Noh *pai) {
    if (arvore == NULL) {
        return;
    }
    arvore->pai = pai;
    preencherPaiInterno(arvore->esq, arvore);
    preencherPaiInterno(arvore->dir, arvore);
}

// Funciona como um embrulho para a função que irá realizar o trabalho 
// de verificar realmente.
int verificarBinariaDeBusca(Noh *arvore) {
    if (arvore == NULL) {
        return 1;
    }
    int resultado = 1;
    verificarBinariaDeBuscaInterno(arvore, &resultado);
    return resultado;
}

void verificarBinariaDeBuscaInterno(Noh *arvore, int *resultado) {
    // No início de cada um dos if's principais estamos verificando se o resultado 
    // é diferente de 0, pois caso seja igual a 0, não precisaremos continuar 
    // verificando os outros nós

    if (arvore->esq != NULL && (*resultado) != 0) {
        if (arvore->esq->valor > arvore->valor) {
            (*resultado) = 0;
            return;
        }
        verificarBinariaDeBuscaInterno(arvore->esq, resultado);
    }
    if (arvore->dir != NULL && (*resultado) != 0) {
        if (arvore->dir->valor <= arvore->valor) {
            (*resultado) = 0;
            return;
        }
        verificarBinariaDeBuscaInterno(arvore->dir, resultado);
    }
}

int *transformarArvoreEmArray(Noh *arvore, int *tamanho) {
    // Por padrão, iremos alocar um espaço na memória do tamanho de 10 inteiros
    int pos = 0;
    int tamAtual = 10;
    int *array = (int *) malloc(tamAtual * sizeof(int));
    inserirElementosArray(arvore, &array, &pos, &tamAtual);
    // Pode ser que alocamos um tamanho de 10 inteiros, mas somente 4 posições foram ocupadas 
    // e portanto, o resto das posições é lixo. Precisamos informar o tamanho real, que é 4.
    // Se tivermos apenas um elemento na árvore, então a posição atual é 0, 
    // em seguida, inserimos esse único elemento no array e incrementamos a posição atual para 1
    // Ou seja, sempre no final a posição irá representar a quantidade real de elementos dentro do array
    (*tamanho) = pos; 
    return array;
}

void inserirElementosArray(Noh *arvore, int **array, int *posicao, int *tamAtual) {
    if (arvore == NULL) {
        return;
    }
    inserirElementosArray(arvore->esq, array, posicao, tamAtual);
    if ((*posicao) >= (*tamAtual)) {
        (*tamAtual) = (*tamAtual) * 2;
        (*array) = realloc(*array, (*tamAtual) * sizeof(int));
    }
    (*array)[(*posicao)] = arvore->valor;
    (*posicao)++;
    inserirElementosArray(arvore->dir, array, posicao, tamAtual);
}

Noh *arrayParaArvoreBalanceada(int *array, int posInicial, int posFinal) {
    if (posFinal < posInicial || posInicial > posFinal) {
        return NULL;
    } 
    int meio = (posFinal - posInicial) / 2 + posInicial;
    Noh *noh = novoNoh(array[meio]);
    noh->esq = arrayParaArvoreBalanceada(array, posInicial, meio - 1);
    noh->dir = arrayParaArvoreBalanceada(array, meio + 1, posFinal);
    return noh;
}

Noh *procurarPaiDeNoh(Noh *arvore, Noh *noh) {
    if (arvore == NULL || arvore->valor == noh->valor) {
        return NULL;
    }
    if  (arvore->esq->valor == noh->valor || arvore->dir->valor == noh->valor) {
        return arvore;
    } 
    if (noh->valor < arvore->valor) {
        return procurarPaiDeNoh(arvore->esq, noh);
    } 
    if (noh->valor > arvore->valor) {
        return procurarPaiDeNoh(arvore->dir, noh);
    }
}