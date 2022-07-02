#include <stdio.h>
#include <stdlib.h>
#include "node.h"
int main() {

    char p1[7] = "abacate";
    char p2[5] = "bolsa";
    char p3[8] = "fernando";
    char p4[3] = "sim";
    char p5[5] = "tchau";
    char p6[6] = "bomdia";

    // 4 6 8 10 13
    // 8 10 10 13
    // 
    Text t1;
    t1.quantity = 6;
    t1.content = p1;

    Text t2;
    t2.quantity = 8;
    t2.content = p2;

    Text t3;
    t3.quantity = 13;
    t3.content = p3;

    Text t4;
    t4.quantity = 10;
    t4.content = p4;

    Text t5;
    t5.quantity = 4;
    t5.content = p5;

    Node *node = create();

    insert(&node, t1, NULL);
    insert(&node, t2, NULL);
    insert(&node, t3, NULL);
    insert(&node, t4, NULL);
    insert(&node, t5, NULL);
    print(node);

    /* removeMin(&node);
    removeMin(&node);
    removeMin(&node);
    removeMin(&node); */

    /* printf("\nPrint ao remover elementos:\n");
    print(node); */

    /* Text t6;
    t6.quantity = 15;
    t6.content = p5;
    insert(&node, t6, NULL); */

    printf("\n");
    //Node *nMin = removeMin(&node);
    //print(node);
   // printf("\nKey tree nMin: %d", nMin->tree->key);
    NodeTree *tree = generateHuffmanTree(&node);
    printf("HAHAHAHA");
    printf("\nKey tree generated: %d\n", tree->key);

    printf("\n");
    printTree(tree);
    //print(node);
    return 0;
}