#include <string>
using std::string;

class Aluno {
    public:
        Aluno(string nome, int qtdNotas);
        ~Aluno();
        void setRA(int r);
        int getRA() const;
        void setNome(string n);
        string getNome() const;
        void addNota(float nt, int posicao);
        float getNota() const;
        void imprimirNotas();
        static int getQtdAlunos();
        static int getContadorRA();
    private: 
        const int ra;
        string nome;
        float * notas; // Vetor dinâmico de notas
        int qtdNotas;
    
    static int qtdAlunos;  // Atributo da classe e não do objeto
    static int contadorRA;
};