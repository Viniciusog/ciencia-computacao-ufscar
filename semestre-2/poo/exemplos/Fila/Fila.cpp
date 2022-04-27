#include <iostream>
#include "Fila.h"

#define VAZIA 0
#define CHEIA 1
#define NORMAL 2

using std::cout;
using std::endl;

int Fila::contadorFilas = 0;

Fila::Fila(int tamanho) {
    tamanho = tamanho;
    inicio = 0;
    proximo = 0;
    estado = 0;
    vetor = new char[tamanho];
    contadorFilas++;
}

Fila::~Fila() {
    delete [] vetor;
    contadorFilas--;
}

void Fila::setEstado(int estado) {
    this->estado = estado;
}

// Altera o tamanho atual da fila
void Fila::Set_tamanho_maximo(int novo_tamanho) {
    vetor = new char[novo_tamanho];
    tamanho = novo_tamanho;
    inicio = 0;
    proximo = 0;
    estado = VAZIA;
}

int Fila::getContadorFilas() {
    return contadorFilas;
}

int Fila::getEstado() const {
    return estado;
}


// Insere elemento na fila
// Não pode inserir elemento se a fila estiver cheia
void Fila::inserir(char valor) {
    if (estado == CHEIA) {
        cout << "Fila está cheia!" << endl;
        return;
    }

    vetor[proximo] = valor;

    // Configuração da fila circular
    if (proximo == tamanho - 1) {
        proximo = 0;
    } else {
        proximo++;
    }

    // Se o próximo chegou no início, então significa que a fila está cheia
    if (proximo == inicio) {
        setEstado(CHEIA); 
    } else {
        setEstado(NORMAL); 
    }
}

//Remover os elementos da fila
char Fila::remover() {
    if (estado == VAZIA) {
        cout << "A fila está vazia!" << endl;
        return '\0';
    }

    char valor = vetor[inicio];

    //Configuração da fila circular
    if (inicio == tamanho - 1) {
        inicio = 0;
    } else {
        inicio++;
    }

    //Se o início chegou no próximo, então significa que a fila está vazia
    if (inicio == proximo) {
        setEstado(VAZIA);
    } else {
        //Se a fila estiver cheia, ela só sairá do estado de CHEIA caso removermos algum item, pois
        //assim o estado será colocado como NORMAL
        setEstado(NORMAL);
    }
    return valor;
}

// Imprime os elementos da fila
void Fila::imprimir() {
    Fila *fAux = new Fila(this->tamanho);
    while (this->estado != VAZIA) {
        char valor = this->remover();
        cout << valor << " ";
        fAux->inserir(valor);
    } 

    while (fAux->estado != VAZIA) {
        char valor = fAux->remover();
        this->inserir(valor);
    }

    delete fAux;
}