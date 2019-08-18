// unreachable.c
// from a start vertex find all vertices that are unreachable
/* An alternative method is to use so-called 'fixed-point' computation.

initialise:
a reachable set comprising of just the start vertex
every other vertex is considered unreachable
check every unreachable vertex v

if there is an edge from a vertex in the reachable set to v

then add v to the reachable set

repeat the previous step until the reachable set does not change
if the reachable set does not change, terminate
When the set does not change, we have reached a 'fixed point'

the set of vertices in the reachable set can be reached from the start vertex
all other vertices cannot be reached */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"
#include "Quack.h"

#define WHITESPACE 100
#define MAX_VERTICES 100

int readNumV(void) { // returns the number of vertices numV or -1
   int numV;
   char w[WHITESPACE];
   scanf("%[ \t\n]s", w);  // skip leading whitespace
   if ((getchar() != '#') ||
       (scanf("%d", &numV) != 1)) {
       fprintf(stderr, "missing number (of vertices)\n");
       return -1;	puts("running eulerianCycle...\n");
   }
   return numV;
}

int readGraph(int numV, Graph g) { // reads number-number pairs until EOF
   int success = true;             // returns true if no error
   int v1, v2;
   while (scanf("%d %d", &v1, &v2) != EOF && success) {
       if (v1 < 0 || v1 >= numV || v2 < 0 || v2 >= numV) {
          fprintf(stderr, "unable to read edge\n");
          success = false;
       }
       else {
          insertEdge(newEdge(v1, v2), g);
       }
   }
   return success;
}

int main (void){
	printf("running unreachable...\n");
    int numV;
    if ((numV = readNumV()) >= 0) {
        Graph g = newGraph(numV);
        if (readGraph(numV, g)) {
            showGraph(g);
        }
        
        // initialise: a reachable set comprising of just the start vertex
        int reachable[MAX_VERTICES] = {0};
        reachable[0] = 1;        
        int new_vertex = 1;  // flag to see if a new vertex was discovered
        int vertex_counter = 0;  // number of vertices in the reachable array
        // loop until now new vertices discovered
        while (new_vertex){
        	new_vertex = 0;  // reset new_vertex flag to 0
        	// outer loop: looping across unreachable vertex
        	for (int vertex_i=0; vertex_i < numV; vertex_i ++){
        		if (reachable[vertex_i] == 0){
		    		printf("checking if unreachable vertex %d is reachable using current reachable set\n", vertex_i);
		    		// checking if the outer loop's unreachable vertex is reachable using a vertex
		    		// in the inner loop (vertices in the reachable vertex)
		    		for (int vertex_j=0; vertex_j < numV; vertex_j ++){
		    			if (reachable[vertex_j]){
							printf("\tchecking if reachable using %d... ", vertex_j);
							if (isEdge(newEdge(vertex_i, vertex_j), g)){
								printf(" reachable");
								reachable[vertex_i] = 1;
								new_vertex = 1;
								vertex_counter ++;
							}
							else if (vertex_i != vertex_j) {
								printf(" unreachable");
							}
							putchar('\n');
		    			}
		    		}
		    	}
        	}
        }
		printf("Unreachable vertices =");
		for (int vertex_k=0; vertex_k < numV; vertex_k++){
			if (reachable[vertex_k] == 0){
				printf(" %d", vertex_k);
			}
		}
		printf("\n");
        freeGraph(g);
		EXIT_SUCCESS;
    }
    else {
		fprintf(stderr, "ERROR: load graph");
		EXIT_FAILURE;
	}
}














