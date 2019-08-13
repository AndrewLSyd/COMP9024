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
	x = atoi(argv[1]);
	y = atoi(argv[2]);
	z = atoi(argv[3]);
	printf("x is %d, y is %d, z is %d\n", x, y, z);
	printf("the sum of x, y, z is %d", x + y + z);

	return EXIT_SUCCESS;
}
