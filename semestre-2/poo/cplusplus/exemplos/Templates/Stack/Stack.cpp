#include "Stack.h"
using std::string;
using namespace std;

template<typename T>
Stack<T>::Stack(int tam) : tamanho(tam > 0 ? tam : 10 ) {
    pilha = new T[tamanho];
    topo = 0;
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