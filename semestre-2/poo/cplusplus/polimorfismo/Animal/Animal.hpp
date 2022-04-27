#include <cstdlib>
#include <iostream>

using namespace std;

class Animal {
    public:
        Animal(string);
        ~Animal();
        void setNome(string nome);
        virtual void fazerBarulho() const; 
        void comer() const;
    private:
        string nome;
};