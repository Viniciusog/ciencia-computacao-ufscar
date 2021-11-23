// Vinícius de Oliveira Guimarães
//RA: 802431

#include <stdio.h>
#include <stdlib.h>

struct venda {
    unsigned int codigo;
    char comentario[50];
    double quantidade;
    double valor;
};

int main()
{
    struct venda minhaVenda;
    
    struct venda * vendas;
    vendas = (struct venda *) calloc(1, sizeof(minhaVenda));
    
    int tamanho = 0;
    
    FILE * arquivo;
    arquivo = fopen("vendas.dat", "r");
    
    if (arquivo == NULL) {
    	printf("Erro ao abrir arquivo.");
    }
    
    while (fread(&minhaVenda, sizeof(minhaVenda), 1, arquivo)) {
        
        // Se for a primeira passada, seto a primeira venda no array de vendas
        if (tamanho == 0) {
            vendas[0] = minhaVenda;
            tamanho++;
        } else {
            // Vamos verificar se a minhaVenda do produto específico já está dentro do array
            int estaNoArray = 0;
            int indexCasoJaTenhaVenda;
            for (int i = 0; i < tamanho; i++) {
                if (vendas[i].codigo == minhaVenda.codigo) {
                    estaNoArray = 1;
                    indexCasoJaTenhaVenda = i;
                }
            }
            // Se a venda já estiver dentro do array, então vamos incrementar a quantidade da venda
            if (estaNoArray == 1) {
                vendas[indexCasoJaTenhaVenda].quantidade += minhaVenda.quantidade;
            } 
            // Se a venda não estiver no array, aumenta o tamanho do array em +1 e coloca a venda dentro
            else {
                tamanho++;
                vendas = realloc(vendas, tamanho * sizeof(minhaVenda));
                vendas[tamanho-1] = minhaVenda;
            }
            
            estaNoArray = 0;
        }
    }
    
    fclose(arquivo);
    
    // Imprimir as vendas que estão dentro do array de vendas de cada produto
    for (int i = 0; i < tamanho; i++) {
        printf("\n");
        printf("Código: %d\n", vendas[i].codigo);
        printf("Comentário: %s\n", vendas[i].comentario);
        printf("Quantidade: %lf\n", vendas[i].quantidade);
        printf("Valor: %lf\n", vendas[i].valor);
        printf("\n");
    }

    return 0;
}