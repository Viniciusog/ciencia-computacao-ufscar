#include <string>
using std::string;

class Animal {
    public:
        Animal(string);
        void setNome(string);
        string getNome();
        void fazerBarulho();
    private:
        string nome;
};