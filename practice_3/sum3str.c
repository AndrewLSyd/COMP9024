// Assume you have the following string declarations:
// Toggle line numbers

//   1 char *r = "1";
//   2 char *s = "23";
//   3 char *t = "456";

// Write a short program that uses the sscanf() function to read these 3 
// strings, sums them as if they were integers, and then prints the total on
// stdout. (Remember a scanf() returns an int, which is the number of
// arguments it has read.) 

#include <stdlib.h>
#include <stdio.h>

char *r = "1";
char *s = "23";
char *t = "456";

int main(void){
	char x[20], y[20], z[20];
	sscanf(r, "%s", x);
	sscanf(s, "%s", y);
	sscanf(t, "%s", z);
	printf("%s, %s, %s\n", x, y, z);
	fputs("converting to int...\n", stdout);
	int x_int, y_int, z_int;
	x_int = atoi(x);
	y_int = atoi(y);
	z_int = atoi(z);
 	printf("%d, %d, %d\n", x_int, y_int, z_int);
	fputs("adding them up...\n", stdout);
	printf("%d\n", x_int + y_int + z_int);
	return EXIT_SUCCESS;
}








