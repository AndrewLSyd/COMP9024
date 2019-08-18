#include <stdlib.h>
#include <stdio.h>


int recount(int x){
	// base case
	if (x==0){
		fputs("0", stdout);
		return 0;
	}
	// recursive case
	recount(x - 1);
	printf(", %d", x);
	return 0;
}



int main(int argc, char *argv[]) {
   int endcount = 0;

	// read in as endcount as int and do error handling
   if ((argc != 2) || (sscanf(argv[1], "%d", &endcount) != 1)) {
      fprintf(stderr, "Usage: %s number\n", argv[0]);
      return(EXIT_FAILURE);
   }
   else {
		recount(endcount);
		putchar("\n");
	}
      return EXIT_SUCCESS;
}

