// Aluno: Vinícius de Oliveira Guimarães
// RA: 802431
// Curso: Ciência da Computação

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void imprime(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

// Função para intercalar as duas partes (subvetores) do vetor principal
void intercala(int array[], unsigned long long *inversoes, int p, int q, int r) {
    int i, j, tam;
    i = p;
    j = q;
    tam = r - p;

    int *w = malloc(tam *sizeof(int));
    int k = 0;
    while (i < q && j < r) {
        if (array[i] <= array[j]) {
            w[k] = array[i];
            i++;
            k++;
        } else {
            // Se array[j] é menor do que array[i],
            // então isso significa que o elemento da posição j
            // está invertido com os da posição i até q-1
            // portanto, a quantidade de elementos invertidos com array[j] será
            // dado por: inversoes = q - i
            *inversoes += q - i;
            w[k] = array[j];
            k++;
            j++;
        }
    }

    while (i < q) { w[k] = array[i]; k++; i++; }

    while (j < r) { w[k] = array[j]; k++; j++; }

    for (int k = 0; k < tam; k++) {
        array[p + k] = w[k];
    }
    free(w);
}

// Função de ordenação que ordena na "subida" da chamada recursiva
// A contagem da quantidade de elementos invertidos será feito durante a intercalação
// dos elementos do array
void mergeSort(int array[], unsigned long long *inversoes, int p, int r) {
    if (r - p > 1) {
        int m  = (r + p) / 2;
        mergeSort(array, inversoes, p, m);
        mergeSort(array, inversoes, m, r);
        intercala(array, inversoes, p, m, r);
    }
}

int main(int argc, char *argv[])
{
    char file_name[MAX];
    FILE *entrada;
    int i, n;
    unsigned long long num_inv = 0;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }
    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNao encontrei o arquivo! Informe o nome da instancia\n");
        exit(EXIT_FAILURE);
    }
    // lendo do arquivo da instância
    fscanf(entrada, "%d", &n);
    int *v = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        fscanf(entrada, "%d", &v[i]);
    
    // Inicializa o valor de inversões para que consiga incrementar a variável
    num_inv = 0;

    // Realiza ordenação do vetor, contando a quantidade de 
    // elementos invertidos na parte da intercalação
    mergeSort(v, &num_inv, 0, n);

    // Imprimi a quantidade de elementos invertidos
    printf("%llu\n", num_inv);

    fclose(entrada);
    return 0;
}
