#include <string>
using std::string;

class Aluno {
    public:
        Aluno(int qtdNotas, string nome);
        ~Aluno();
        string getNome();
        int getQtdNotas();
        int getRA();
        void setNome(string nome);
        void setNota(float nota, int posicao);
        int getContadorRA();
        int getQtdAlunos();
        void imprimir();
    private:
        string nome;
        int ra;
        float * notas;
        int qtdNotas;
        static int contadorAlunos;
        static int contadorRA;

};