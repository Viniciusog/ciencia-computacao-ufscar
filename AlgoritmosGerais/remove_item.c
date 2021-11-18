remove_item(int array[], int *tamanho, int numero) {
    int indexParaRemover = -1;
    for (int i = 0; i < tamanho; i++) {
        if (vet[i] == numero) {
            indexParaRemover = i;
        }
    }

    if (indexParaRemover != -1) {
        vet[indexParaRemover] = vet[tamanho-1];
        *tamanho = *tamanho -1;
    }

}