
//insere na última posição do array e vai fazendo o sobre heap
int inserir(int v[], int n, int valor);
//remove a primeira posição do array (coloca o valor da última posição do array na primeira posição do array)
//e em seguida, vai fazendo o desce heap com esse valor que agora está na primeira posição da heap
int remover(int v[], int n);
int pai(int index); //(i - 1) / 2
int filhoEsq(int index); // 2i + 1
int filhoDir(int index); // 2i + 2
void troca(int *n1, int *n2);
int indexMaiorFilho(int v[], int index);
void CorrigeHeapSubindo(int v[], int lastPosition); //sobe heap
void desceHeap(int v[], int n, int indexInicial);
void imprimir(int v[], int n);