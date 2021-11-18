/*
    Aluno: Vinícius de Oliveira Guimarães
    Ciência da Computação
*/

#include <stdio.h>
int tamanhoColuna = 0;

// Calcula o valor que as linhas, colunas e diagonais devem ter por padrão
// tamanho padrão = dimensao * (dimensao² + 1) / 2
int valorPadraoLinColDiag(int n) {
    return (n * (n * n + 1)) / 2;
}

int calcularSomaDiagonalPrincipal(int matriz[][tamanhoColuna], int dimensao) {
    int i = 0; // linha e coluna
    int somaDiagonalPrincipal = 0;
    while (i < dimensao) {
        somaDiagonalPrincipal = somaDiagonalPrincipal + matriz[i][i];
        i++;
    }
    return somaDiagonalPrincipal;
}

int calcularSomaDiagonalSecundaria(int matriz[][tamanhoColuna], int dimensao) {
    int k = 0; // linha
    int j = dimensao - 1; // coluna
    int somaDiagonalSecundaria = 0;
    while (k < dimensao && j >= 0) {
        somaDiagonalSecundaria = somaDiagonalSecundaria + matriz[k][j];
        k = k + 1;
        j = j - 1;
    }
    return somaDiagonalSecundaria;
}


int main()
{
    int dimensao;
    // Começa sendo mágico (1)
    int flagMagico = 1;
    
    scanf("%d", &dimensao);
    tamanhoColuna = dimensao;
    
    int matriz[dimensao][dimensao];
    // dimensao * (dimensao² + 1) / 2
    int valorPadraoLCD = valorPadraoLinColDiag(dimensao);
    
    // Ler a matriz
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            scanf("%i", &matriz[i][j]);
        }
    }
    
    // Verificar se a soma das linhas e colunas são iguais
    int somaComumLinha = 0;
    int somaComumColuna = 0;
    for (int i = 0; i < dimensao; i++) {
        int somaLinha = 0;
        int somaColuna = 0;
        for (int j = 0; j < dimensao; j++) {
            // Cálculo das linhas
            somaLinha = somaLinha + matriz[i][j];
            // Cálculo das colunas
            somaColuna = somaColuna + matriz[j][i];
            
            // Verificar se o número está entre 1 e dimensao²
            if (matriz[i][j] < 1 || matriz[i][j] > (dimensao*dimensao)) {
                flagMagico = 0;
                break;
            }
        }
        
        if (i == 0) {
            somaComumLinha = somaLinha;
            somaComumColuna = somaColuna;
        } else {
            if (somaLinha != somaComumLinha || somaColuna != somaComumColuna || somaComumLinha != somaComumColuna) {
                flagMagico = 0;
                break;
            }
            if (somaLinha !=  valorPadraoLCD || somaColuna != valorPadraoLCD) { 
                flagMagico = 0;
                break;
            }
        }
    }
    
    // Soma das diagonais, principal e secundária.
    int somaDiagonalPrincipal = calcularSomaDiagonalPrincipal(matriz, dimensao);
    int somaDiagonalSecundaria = calcularSomaDiagonalSecundaria(matriz, dimensao);
 
    // Verifica se a soma das diagonais são válidas
    if (somaDiagonalPrincipal != somaDiagonalSecundaria || somaDiagonalPrincipal != valorPadraoLCD || somaDiagonalSecundaria != valorPadraoLCD) {
        flagMagico = 0;
    }
    
    if (flagMagico == 0) {
        printf("invalido");
    } else {
        printf("valido");
    }

    return 0;
}
