// eulerianCycle.c

// what determines whether a graph is Eulerian or not?
// a connected graph has a Eulerian cycle if all its vertices have even degree
// check this first, then use Albert's program to print out the path

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

Vertex getAdjacent(Graph g, int numV, Vertex v) {
   Vertex retv = -1; // assume no adj. vertices
   for (Vertex w = numV-1; w >= 0 && retv == -1; w--) { 
      if (isEdge(newEdge(v, w), g)) {
         retv = w;   // found largest adj. vertex
      }
   }
   return retv;
}


void findEulerianCycle(Graph g, int numV, Vertex startv) {
	// can start with any vertex...
   Quack s = createQuack();
   char out_str[MAX_VERTICES];
   int counter=0;

   push(startv, s);
   while (!isEmptyQuack(s)) {
      Vertex v = pop(s); // pop and then ...
      push(v, s);        // ... push back on, so no change
      Vertex w = getAdjacent(g, numV, v); // get largest adj. v
      if (w >= 0) {      // if true, there is an adj. vertex
         push(w, s);     // push this vertex onto stack
         removeEdge(newEdge(v, w), g); // remove edge to vertex
      }
      else {             // top v on stack has no adj. vertices
         w = pop(s);
         out_str[counter] = w + '0';
         counter ++;
         // printf("%d ", w);
      }
   }
   out_str[counter] = '\0';
   if (counter > 1){
	   printf("Eulerian cycle from %d: ", startv);
	   printf("%s\n", out_str);
   }
}



int main (void) { 
	puts("running eulerianCycle...\n");
    int numV;
    if ((numV = readNumV()) >= 0) {
        Graph g = newGraph(numV);
        if (readGraph(numV, g)) {
            showGraph(g);
        }
        
        // array which keeps track of degree of all vertices
		int degree[MAX_VERTICES] = {0};  // initialise all to 0
		for (int vertex=0; vertex < numV; vertex++){
			// loop through all vertices to count degree
			for (int vertex_2=0; vertex_2 < numV; vertex_2++){  
				// printf("checking %d and %d\n", vertex, vertex_2);
				if (isEdge(newEdge(vertex, vertex_2), g)){
					degree[vertex]++;
				}
			}    	    	
		}
		
		// printing array
		puts("degree array");
		for (int i=0; i < numV; i++){
			printf("-%d-", degree[i]);
			if (degree[i] % 2 != 0){  // if not even
				fprintf(stderr, "no Eulerian cycle as degree is not all even\n");
				exit(1);
			}			
		}
		putchar('\n');
		
		for (int startv=0; startv < numV; startv++){
			findEulerianCycle(g, numV, startv);
		}
     
        g = freeGraph(g);       
        
    }
    else {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


