#include <stdio.h>
#include "Insertion.h"

int main() {
    int v[] = {7,3,5,1,6,9,4,2,8};
    printf("\nINSERTION SORT\n");
    insertionSort(v, 9);
    print(v, 9);

    int v2[] = {7,3,5,1,6,9,4,2,8};
    printf("\nINSERTION SORT MELHORADO\n");
    insertionSortMelhorado1(v2, 9);
    print(v2, 9);
}