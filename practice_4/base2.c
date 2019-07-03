// base2.c

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv){
	if (argc != 2){
		fprintf(stderr, "Usage: ./base2 number\n");
		return EXIT_FAILURE;
	}
	printf("you have entered %s\n", *(argv + 1));
	printf("converting this to an integer using atoi... %d\n", atoi(*(argv + 1)));
	int my_num;
	sscanf(*(argv + 1), "%d", &my_num);
	printf("converting this to an integer using sscanf... %d\n", my_num);
	return EXIT_SUCCESS;
}
