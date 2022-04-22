#include "stdio.h"
#include "BubbleSort.h"

int main() {
    int v[] = {7,3,5,1,6,9,4,2,8};
    BubbleSort(v, 9);
    print(v, 9);
}