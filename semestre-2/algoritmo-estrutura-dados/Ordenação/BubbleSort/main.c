#include "stdio.h"
#include "BubbleSort.h"

int main() {
    int v[] = {7,3,5,1,6,9,4,2,8};
    bubbleSort(v, 9);

    int v2[] = {6,9,3,5,1,8,7,4};
    bubbleSortMenorInicio(v2, 8);
    printf("\n---V2---\n");
    print(v2, 8);
}