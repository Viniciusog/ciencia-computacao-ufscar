
#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

int main() {

    int v[] = {9,7,8,6,4,3,5};
    int lastPos = 6;
    int isH = isHeap(v, lastPos);
    printf("É max heap? %s", isH == 1 ? "Sim" : "Não");
}