#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
using std::getline;


class Animal {
    public:

        Animal(string n) {
            setNome(n);
        }

        string getNome() {
            return nome;
        }

        void setNome(string n) {
            nome = n;
        }

        void fazerBarulho() {
            cout << "Barulho do: " << nome <<endl;
        }
    private:
        string nome;
};

int main() {

    string nomeDoAnimal;
    Animal a("Nome padrão");

    cout << "Insira o nome do animal" << endl;
    getline(cin, nomeDoAnimal); // lê nome do animal com espaço em branco
    cout << endl; // Gera espaço em branco

    a.setNome(nomeDoAnimal);

    a.fazerBarulho();
    return 0;
}