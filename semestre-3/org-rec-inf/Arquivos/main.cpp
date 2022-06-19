#include <iostream>
using namespace std;
#include <fstream>

int main() {
    ofstream arqEscrever("teste.txt");
    
    arqEscrever << "Alguma coisa";
    return 0;
}

