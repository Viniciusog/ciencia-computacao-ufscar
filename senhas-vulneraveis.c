#include <stdio.h>

int main(int argc, char const *argv[])
{
    int pontuacoesCadaNumero[10] = {0};
    int senhas[5] = {8765, 9776, 1332, 1432, 1765};
    int senhasDigitos[5][5]; // senha // dígito -> o 5º dígito funciona como uma pontuação para saber quantos dígitos comuns essa palavra tem
    
    int i, j, k;
    for (i = 0; i < 5; i++) { // Para cada senhas
        
        // PEGAR OS DÍGITOS
        int escolhidos[4] = {0};
        int digitos[4] = {0};
        
        int n1 = senhas[i]/1000;
        int aux = senhas[i]/100;
        int n2 = aux - n1 * 10;
        int aux2 = senhas[i]/10;
        int n3 = aux2 - aux * 10;
        int n4 = senhas[i] - aux2 * 10;
        
        // Adicionar os dígitos em um array de dígitos
        digitos[0] = n1;
        digitos[1] = n2;
        digitos[2] = n3;
        digitos[3] = n4;
        
        int index = 0;
        for (int l = 0; l < 4; l++) { // Para cada dígito da senha
            
            // Vou adicionar esse dígito na matriz de senhas/dígitos.
            // A posição [i][5] é uma posição especial e serve como um código de pontuação.
            senhasDigitos[i][l] = digitos[l];

            int jaTem = 0;
            // Percorrer cada item do escolhidos verificando se o dígito atual está lá
            for (int m = 0; m < 4; m++) { 
                if (digitos[l] == escolhidos[m]) {
                    jaTem = 1;
                }
            }
            
            // Se o dígito atual não estiver no array 'escolhidos', então iremos colocar
            if (jaTem == 0) {
                escolhidos[index] = digitos[l];
                index = index + 1;
            }
        }
        
        // Em seguida, adiciona +1 na posição que cada um dos números escolhidos representam
        for (int m = 0; m < 4; m++) {
            if (escolhidos[m] != 0) {
                pontuacoesCadaNumero[escolhidos[m]] = pontuacoesCadaNumero[escolhidos[m]] + 1;
            }
        }    
    }
    
   
    printf("\nPontuação de cada número (Vezes que apareceram em senhas diferentes):\n");
    printf("Número:    0 1 2 3 4 5 6 7 8 9\n");
    printf("Pontuação: ");
    
    // Pega a pontuação do número mais frequente 
    // (Quantidade de vezes que um número aparece em senhas diferentes)
    int maiorPontuacao = pontuacoesCadaNumero[0];
    int numero = -1;
    for (int i = 0; i < 10; i++) {
        printf("%d ", pontuacoesCadaNumero[i]);
        if (pontuacoesCadaNumero[i] >= maiorPontuacao) { 
            maiorPontuacao = pontuacoesCadaNumero[i];
            numero = numero + 1;
        }
    }
    
    printf("\n");
    
    // Pega os números com maior pontuação.
    // (Que aparecem em senhas diferentes a maior quantidade de vezes)
    int array[numero];
    int indice = 0;
    
    // Percorrer o array que tem a pontuação de cada número
    for (int i = 0; i < 10; i++) {
        // Se a pontuação do número i for igual a maior pontuação, então sabemos
        // que esse número é um dos mais comuns (mais frequente)
        if (pontuacoesCadaNumero[i] == maiorPontuacao) { 
            // Adiciona esse número mais frequente na lista de números mais frequentes
            array[indice] = i;
            indice = indice + 1;
        }
    }

    // VERIFICAR QUAIS SENHAS POSSUEM A MAIOR QUANTIDADE DE NÚMEROS FREQUENTES
    
    printf("\nDígitos das senhas:\n");
    // Para cada senha
    for (int i = 0; i < 5; i++) {
        // Iremos contar a quantidade de números frequentes na senha
        int numeroDigitosComuns = 0;
        // Percorre cada dígito da senha
        
        for (int j = 0; j < 4; j++) {
            printf("%d ", senhasDigitos[i][j]);
            // Verifica se o dígito pertence a um dos números mais frequentes.
            // Se pertencer, então adicionaremos +1 na variável numeroDigitosComuns
            for (int l = 0; l < numero; l++) {
                // Se o dígito for igual a um dos mais frequentes...
                if (senhasDigitos[i][j] == array[l]) {
                    numeroDigitosComuns = numeroDigitosComuns + 1;
                    // Adicionaremos a pontuação especial para essa senha,
                    // Ou seja, na posição [i][5], colocaremos a quantidade de 
                    // números frequentes que esta senha possui
                    senhasDigitos[i][5] = numeroDigitosComuns;
                }
            }
        }
        printf("\n");
    }
    
   
    printf("\nSENHAS VULNERÁVEIS:\n");
    // Para cada senha, iremos verificar se esta senha contém a maior quantidade de dígitos frequentes
    // contabilizados na variável maiorQtdDeNumerosFrequentes.
    // Se tiver a maior quantidade de dígitos frequentes, então mostraremos na tela
    for (int i = 0; i < 5; i++) {
        if (senhasDigitos[i][5] >= 2) {
            printf("%d \n",senhas[i]);
        }
    } 
    return 0;
}