// print out memory address
#include <stdio.h>
#include <stdlib.h>

int x, y, z;

int main(void){
    printf("%p %p %p", &x, &y, &z);
}