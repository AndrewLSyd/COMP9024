// sum3argA.c

// Write a short program that uses sscanf() to read 3 strings from the command 
// line. If the arguments are all numerical, the program should sum them, and 
// print the total.

// What happens if one or more of the arguments is not an integer? For example, 
// try ./sum3argA 1 z 3

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv){
	printf("you have entered %d arguments\n", argc - 1);
	for (int i=1; i < argc; i ++){
		printf("argument %i is %s\n", i, argv[i]);
	}
	int x, y, z;
	sscanf(argv[1], "%d", &x);
	sscanf(argv[2], "%d", &y);
	sscanf(argv[3], "%d", &z);
	printf("x is %d\n", x);
	printf("y is %d\n", y);
	printf("z is %d\n", z);

	printf("the sum of x, y, z is %d", x + y + z);

	return EXIT_SUCCESS;
}
