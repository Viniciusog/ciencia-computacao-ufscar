#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Aluno: Vinícius de Oliveira Guimarães

struct registro {
    int *v;
    int tam;
};


// Retorna apenas os elementos de um array que estejam dentro de um determinado intervalo
struct registro numerosEntreExtremos(struct registro reg1, int extInf, int extSup) {
    
    struct registro reg2;
    // Meu vetor do registro correto por padrão terá o tamanho completo do meu array do registro 1
    // Só depois que eu vou redefinir o tamanho do meu vetor para que ele fique apenas com o tamanho necessário
    reg2.v  = (int *) calloc(reg1.tam, sizeof(int));
    reg2.tam = reg1.tam;
    
    int qtdNumerosEntreExtremos = 0;
    
    for (int i = 0; i < reg1.tam; i++) {
        // Se o número no meu array estiver entre os extremos, então adicionarei ele no meu array do reg2
        // Além disso, incrementarei um contador de números entre os extremos, para poder redefinir o tamanho do meu vetor depois que
        // os números de acordo estiverem lá
        if (reg1.v[i] > extInf && reg1.v[i] < extSup) {
            reg2.v[qtdNumerosEntreExtremos] = reg1.v[i];
            qtdNumerosEntreExtremos = qtdNumerosEntreExtremos + 1;
        }
    }
    
    // Agora irei redefinir o tamanho do meu vetor de números entre os extremos para ficar apenas com o tamanho essencial
    reg2.v = realloc(reg2.v, qtdNumerosEntreExtremos * sizeof(int));
    reg2.tam = qtdNumerosEntreExtremos;
    
    return reg2;
}
        
int main() {
    
    struct registro regV;
    regV.v = (int *) calloc(10, sizeof(int));
    regV.tam = 10;
    
    // Setando números aleatórios no meu array
    for (int i = 0; i < 10; i++) {
        regV.v[i] = rand() % 10;
    }
    
    for (int i = 0; i < 10; i++) {
        printf("%d ", regV.v[i]);
    }
    
    struct registro regComNumerosEntreExtremo = numerosEntreExtremos(regV, 2, 6);
    
    printf("\n");
    for (int i = 0; i < regComNumerosEntreExtremo.tam; i++) {
        printf("%d ", regComNumerosEntreExtremo.v[i]);
    }
}