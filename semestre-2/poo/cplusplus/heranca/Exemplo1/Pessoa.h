#include <string>
using std::string;

class Pessoa {
    public:
        Pessoa(string, int);
        ~Pessoa();

        void setNome(string);
        string getNome() const;

        void setIdade(int);
        int getIdade() const;
    private:
        string nome;
        int idade;
};