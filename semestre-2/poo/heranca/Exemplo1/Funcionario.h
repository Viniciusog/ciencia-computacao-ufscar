#include <string>
using std::string;

#include "./Pessoa.h"

class Funcionario : public Pessoa {
    public:
        Funcionario(string, int, int);
        ~Funcionario();
        void setNumeroCarteira(int numero);
        int getNumeroCarteira() const;

    private:
        int numeroCarteira;
};