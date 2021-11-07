// Aluno: Vinícius de Oliveira Guimarães
// Ciência da Computação
// Construção de algoritmos e programação

#include <stdio.h>

// Lê o conjunto
void lerConjunto(int conjunto[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &conjunto[i]);
    }
}

void ordenarArray(int array[], int tamanho) {

    // Temos que realizar o passado que está dentro desse primeiro for, tamanho-1 vezes
    for (int j = 0; j < tamanho; j++) {
        // Pega o maior item e vai levando para o final do array
        for (int i = 0; i < tamanho-1; i++) {
            if (array[i] > array[i + 1]) {
                int aux = array[i];
                array[i] = array[i + 1];
                array[i + 1] = aux;
            }
        }
    }
}

void juntarConjuntos(int array1[], int tamanho1, int array2[], int tamanho2) {
    int soma = tamanho2 + tamanho1;
    // Nosso array que tem os números do maior array e os itens 
    // diferentes do segundo array
    int diferentes[soma];
    
    for (int u = 0; u < soma; u++) {
        diferentes[u] = 0;
    }
    
    int cont = 0;
    
    // Se meu array 1, for maior que o array 2
    if (tamanho1 > tamanho2) {
        
        for (int i = 0; i < tamanho1; i++) {
            diferentes[i] = array1[i];
        }
        
        cont = cont + tamanho1;
        
        // Percorrer os elementos do array 2
        for (int j = 0; j < tamanho2; j++) {
            int temIgual = 0;
            // para cada elemento do array 2, iremos verificar se ele está no array1
            for (int k = 0; k < tamanho1; k++) {
                if (array2[j] == array1[k]) {
                    temIgual = 1;
                    break;
                }
            }
            // Se o item do array 2 nesta posição não tiver no array1
            // Então adicionaremos no array geral
            if (temIgual == 0) {
                diferentes[cont] = array2[j];
                cont = cont + 1;
            }
        }
        
        
    } 
    // Se meu array 2, for maior que o array 1
    else {
        
        for (int i = 0; i < tamanho2; i++) {
            diferentes[i] = array2[i];
        }
        cont = cont + tamanho2;
        
        // Percorrer os elementos do array 1
        for (int j = 0; j < tamanho1; j++) {
            int temIgual = 0;
            temIgual = 0;
            // para cada elemento do array 1, iremos verificar se ele está no array2
            for (int k = 0; k < tamanho2; k++) {
                if (array1[j] == array2[k]) {
                    temIgual = 1;
                }
            }
            
            // Se o item do array 1 nesta posição não tiver no array 2
            // Então adicionaremos no array geral
            if (temIgual == 0) {
                diferentes[cont] = array1[j];
                cont = cont + 1;
            }
        }
    }
    
    // printf("\nQTD DIFERENTES: %d\n", cont);
    ordenarArray(diferentes, cont);
    
    for (int l = 0; l < cont; l++) {
        if (diferentes[l] != 0) {
            printf("%d ", diferentes[l]);
        }
    }
}

int main(int argc, char const *argv[]) {
    int primeiroTamanho;
    int segundoTamanho;

    // Ler o primeiro conjunto
    scanf("%d", &primeiroTamanho);
    int primeiroConjunto[primeiroTamanho];
    lerConjunto(primeiroConjunto, primeiroTamanho);

    // Ler o segundo conjunto
    scanf("%d", &segundoTamanho);
    int segundoConjunto[segundoTamanho];
    lerConjunto(segundoConjunto, segundoTamanho);
    
    // Pegar os items, juntar os arrays
    juntarConjuntos(primeiroConjunto, primeiroTamanho, segundoConjunto, segundoTamanho);
    
    return 0;
}