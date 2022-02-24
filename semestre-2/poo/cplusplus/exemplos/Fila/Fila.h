#ifndef FILA_H
#define FILA_H

class Fila {
    public: 
        Fila(int tamanho);
        ~Fila();
        int getEstado() const;
        static int getContadorFilas();
        char remover();
        void inserir(char valor);
        void Set_tamanho_maximo(int novoTamanho);
        void imprimir();
    private:
        int tamanho;
        char *vetor;
        int estado; // 0=Vazio, 1=Cheio, 2=Nem cheio e nem vazio
        int proximo;
        int inicio;
        void setEstado(int estado);

    static int contadorFilas;
};
#endif