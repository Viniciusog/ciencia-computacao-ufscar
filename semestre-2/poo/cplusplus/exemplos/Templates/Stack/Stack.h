#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template<typename T>
class Stack {
    public:
        Stack(int tamanho = 10);
        ~Stack();
        bool empilhar(T elemento);
        T desempilhar();
        void imprimir();
    private:
        int tamanho;
        T *pilha;
        int topo;        
};

template<typename T>
Stack<T>::Stack(int tam) : tamanho(tam > 0 ? tam : 10 ) {
    pilha = new T[tamanho];
    topo = 0;
}

template<typename T>
Stack<T>::~Stack() {
    cout << "Chamada do destrutor" << endl;
}

template<typename T>
bool Stack<T>::empilhar(T elemento) {
    // Se estiver cheia
    if (this->topo == tamanho) {
        return false;
    }
    pilha[topo] = elemento;
    topo++;
    return true;
}

template<typename T>
T Stack<T>::desempilhar() {
    // Se estiver vazia
    if (topo = 0) {
        return nullptr;
    }
    topo--;
    return pilha[topo];
}

template<typename T>
void Stack<T>::imprimir() {
    for (int i = 0; i < topo; i++) {
        cout << pilha[i] << " "; 
    }
    cout << endl;
}

#endif