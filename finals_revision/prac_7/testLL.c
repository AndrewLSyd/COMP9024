// testLL.c: hard-coded tester for the linked-list ADT
//           put testdata onto the head and tail of a linked list
//           get data from the head and tail of the linked list
//           sum the data while emptying the list
#include <stdio.h>
#include <stdlib.h>
#include "LL.h"

int main() {
    int testdata[7] = {10, 20, 30, 40, 50, 60}; // 1 extra for the '\0'
    List ll = createList();

    printf("Data is:\n\t");  // check what the test data is
    for (int i = 0; i < 6; i++) {
         printf("%d ", testdata[i]);
    }
    putchar('\n');

    int *p = testdata;
    printf("Test 1. Show each putHead of testdata:\n");
    while (*p != '\0') {
        putHead(*p++, ll);
        putchar('\t'); showList(ll);
    }

    printf("Test 2. Show 3 getTails and putHeads:\n");
    for (int i = 0; i < 3; i++) {
        putHead(getTail(ll), ll);
        putchar('\t'); showList(ll);
    }

    printf("Test 3. Show 3 getHeads and putTails:\n");
    for (int i = 0; i < 3; i++) {
        putTail(getHead(ll), ll);
        putchar('\t'); showList(ll);
    }

    printf("Test 4. Show isEmpty working, sum from back onto front\n");
    int oneleft = 0;
    while (!oneleft) {
        int tmp = getTail(ll) + getTail(ll);
        if (isEmptyList(ll)) {
            oneleft = 1;
        }
        putHead(tmp, ll);
        putchar('\t'); showList(ll);
    }

    printf("Test 5. The final act, getHead the sum and check list isEmpty\n");
    int sum = getHead(ll);
    if (isEmptyList(ll)) {
        putchar('\t'); showList(ll);
        printf("\tSum = %d\n", sum);
    }

    return EXIT_SUCCESS;
}

