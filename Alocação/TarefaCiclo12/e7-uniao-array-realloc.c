#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Aluno: Vinícius de Oliveira Guimarães


struct set {
    int *v;
    int n;
};

struct set uniao(struct set set1, struct set set2) {
    int * numeros;
    
    int tamanho;
    
    // Gera o vetor de números
    if (set1.n > set2.n) {
        numeros = calloc(set1.n, sizeof(int));
        
        if (numeros == NULL) {
            printf("Erro ao alocar memória.");
        } else {
            tamanho = set1.n;
        
            for (int i = 0; i < set1.n; i++) {
                numeros[i] = set1.v[i];
            }
            
            // para cada elemento do vetor do set2
            for (int i = 0; i < set2.n; i++) {
                int jaTem = 0;
                // vamos verificar se ele já está no array 'numeros'
                for (int j = 0; j < tamanho; j++) {
                    if (set2.v[i] == numeros[j]) {
                        jaTem = 1;
                        break;
                    }
                }
                
                // Se não tiver dento do nosso array 'numeros', iremos aumentar o tamanho do array 'numeros' em +1
                if (jaTem == 0) {
                    numeros = realloc(numeros, (tamanho + 1) * sizeof(int));
                    if (numeros == NULL) {
                        printf("Erro ao realocar memória");
                    } else {
                        numeros[tamanho] = set2.v[i];
                        tamanho = tamanho + 1;
                    }
                }
            }
        }
        
    } 
    
    else {
        // Caso o vetor do set2 for maior que o vetor do set1, irei adicionar todos os elementos do 
        // vetor do set2 dentro do meu array 'numeros'
        numeros = calloc(set2.n, sizeof(int));
        
        if (numeros == NULL) {
            printf("Erro ao alocar memória.");
        } else {
            tamanho = set2.n;
        
            for (int i = 0; i < set2.n; i++) {
                numeros[i] = set2.v[i];
            }
            
            // Para cada elemento do vetor numérico dentro do set1, irei verificar se o elemento já
            // está dentro do vetor números
            for (int i = 0; i < set1.n; i++) {
                int jaTem = 0;
                for (int j = 0; j < tamanho; j++) {
                    if (set1.v[i] == numeros[j]) {
                        jaTem = 1;
                        break;
                    }
                }
                
                // Se o número do array do set1, não estiver dentro do array 'numeros', então irei 
                // adicioná-lo lá dentro, aumento o tamanho do array em +1 e setando o número do set1, na posição tamanho
                if (jaTem == 0) {
                    numeros = realloc(numeros, (tamanho + 1) * sizeof(int));
                    numeros[tamanho] = set1.v[i];
                    tamanho = tamanho + 1;
                }
            }       
        }
    }
    
    free(set1.v);
    free(set2.v);
    
    struct set setUniao;
    setUniao.v = numeros;
    setUniao.n = tamanho;
    
    return setUniao;
}
        
int main() {
    
    struct set set1;
    struct set set2;
    
    int n1;
    int n2;
    
    int * v1;
    int * v2;
    
    printf("Insira a quantidade de elementos do vetor do set1: ");
    scanf("%d", &n1);
    
    v1 = (int *) calloc(n1, sizeof(int));
    
    
    // Lê os elementos do primeiro vetor
    printf("Insira os elementos do vetor do set1: \n");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &v1[i]);
    }
    
    set1.v = v1;
    set1.n = n1;
    
    printf("Insira a quantidade de elementos do vetor do set2: ");
    scanf("%d", &n2);
    
    v2 = (int *) calloc(n2, sizeof(int));

    printf("Insira os elementos do vetor do set2: \n");
    // Lê os elementos do segundo vetor
    for (int i = 0; i < n2; i++) {
        scanf("%d", &v2[i]);
    }
    
    set2.v = v2;
    set2.n = n2;
    
    struct set setUniao = uniao(set1, set2);
    printf("\n");
    printf("TAMANHO DO VETOR UNIÃO: %d\n", setUniao.n);
    for (int i = 0; i < setUniao.n; i++) {
        printf("%d ", setUniao.v[i]);
    }
}