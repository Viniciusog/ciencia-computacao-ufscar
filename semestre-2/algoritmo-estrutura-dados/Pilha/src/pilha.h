// Feito por: Vin�cius de Oliveira Guimar�es

typedef struct pilha Pilha;

Pilha *criaPilha();
void empilha(Pilha *s, char x);
char desempilha(Pilha *s);
int pilhaVazia(Pilha *s);
int pilhaCheia(Pilha *s);
Pilha *liberaPilha(Pilha *s);

// Fun��es n�o primitivas
void inverterPilha(Pilha *s);
void imprimePilha(Pilha *s);
int tamanhoPilha(Pilha *s);
char maiorValorASCII(Pilha *s);
char consultarTopo(Pilha *s);
void ordenar(Pilha *s, int crescente);
int verificarPilhasIguais(Pilha *s, Pilha *s2);
