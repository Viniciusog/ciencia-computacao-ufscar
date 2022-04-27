#include "Aluno.h"
#include <iostream>
#include <string>
using namespace std;

int main() {    
    Endereco e("Rua legal", "Bairro mais legal");
    Aluno a("fernando", e);
    cout << a;  
}