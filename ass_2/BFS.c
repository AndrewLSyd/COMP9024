#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "Quack.h"
#include "IOmem.h"

#define START 0
#define GOAL  4

void printPath(int *, int, Vertex);
void shortestPath(Graph, Vertex, Vertex, int);

int main(void) {
   int numV;
   if ((numV = readNumV()) > 0) {        // read #vertices
      Graph g = newGraph(numV);
      if (readBuildGraph(g) == 1) {
         showGraph(g);

         printf("Find shortest path from ");
         printf("%d to %d\n", START, GOAL);
         shortestPath(g, START, GOAL, numV);
      }
      freeGraph(g);
      g= NULL;
   }
   else {
      printf("Error in reading #number\n");
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}

void shortestPath(Graph g, Vertex start, Vertex goal, int numV) {
   int *visited = mallocArray(numV);
   int *parent = mallocArray(numV);          // THIS IS NEW

   Quack q = createQuack();
   qush(start, q);
   int order = 0;
   visited[start] = order++;
   int found = 0;
   while (!isEmptyQuack(q) && !found) {      // FOUND TELLS US TO STOP
      Vertex v = pop(q);
      for (Vertex w = 0; w < numV && !found; w++) {
         if (isEdge(newEdge(v,w), g)) {      // for adjacent vertex w ...
            if (visited[w] == UNVISITED) {   // ... if w is unvisited ...
               qush(w, q);                   // ... queue w
               printf("Doing edge %d-%d\n", v, w); // DEBUG
               visited[w] = order++;         // w is now visited
               parent[w] = v;                // w's PARENT is v
               if (w == goal) {              // if w is the goal ...
                  found = 1;                 // ..FOUND IT! NOW GET OUT
               }
            }
         }
      }
   }
   if (found) {
      printf("SHORTEST path from %d to %d is ", start, goal);
      printPath(parent, numV, goal); // print path from START TO GOAL
      putchar('\n');
   }
   else {
      printf("no path found\n");
   }
   printArray("Visited: ", visited, numV);   // debug
   printArray("Parent : ", parent, numV);    // debug
   free(visited);
   free(parent);
   makeEmptyQuack(q);
   return;
}