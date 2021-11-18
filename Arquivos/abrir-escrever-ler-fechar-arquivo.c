#include <stdio.h>

struct pessoa {
    char nome[50];
    int idade;
};

int main() {
    
    struct pessoa minhaPessoa;
    
    int quantidade;
    printf("Insira a quantidade de pessoas para serem cadastradas: ");
    scanf("%d", &quantidade);
    
    for (int i = 0; i < quantidade; i++) {
        
        FILE * arquivo;
        arquivo = fopen("dados.bin", "a");
        
        printf("Insira os dados da %dº pessoa.\n", (i + 1));
        printf("Nome: \n");
        scanf("%s", minhaPessoa.nome);
        printf("Idade: \n");
        scanf("%d", &minhaPessoa.idade);
        
        fwrite(&minhaPessoa, sizeof(minhaPessoa), 1, arquivo);
        
        fclose(arquivo);
    }
    
    
    int ver;
    printf("\nGOSTARIA DE VER AS INFORMAÇÕES CADASTRADAS? (sim=1)\n");
    scanf("%d", &ver);
    
    if (ver == 1) {
        FILE *arquivoLer;
        arquivoLer = fopen("dados.bin", "r");
        
        printf("Dados cadastrados:\n");
        while (fread(&minhaPessoa, sizeof(minhaPessoa), 1, arquivoLer)) {
            printf("Olá %s, você tem %d anos!\n", minhaPessoa.nome, minhaPessoa.idade);
        }
        
        fclose(arquivoLer);
    }
}