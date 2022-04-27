#include <iostream>
#include <string>
using namespace std;

class Endereco {
    public:
        Endereco(string rua, string bairro);
        string getRua() const;
        string getBairro() const;
    private:
        string rua;
        string bairro;
};