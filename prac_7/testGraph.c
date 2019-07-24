// readGraph.c  read a graph from stdin and print it
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

int main (void) { 
    Graph g = newGraph(4);

	insertE(g, newE(0, 1));
	insertE(g, newE(1, 2));
	insertE(g, newE(3, 4));
	insertE(g, newE(0, 4));

	showGraph(g);

	Edge temp_edge = {0, 1};
	printf("is edge {0, 1}, %d\n", isEdge(g, temp_edge));
	Edge temp_edge2 = {0, 0};
	printf("is edge {0, 0}, %d\n", isEdge(g, temp_edge2));
	Edge temp_edge3 = {0, 3};
	printf("is edge {0, 3}, %d\n", isEdge(g, temp_edge3));
	Edge temp_edge4 = {2, 1};
	printf("is edge {0, 1}, %d\n", isEdge(g, temp_edge4));

	g = freeGraph(g);
    g = NULL;

    return EXIT_SUCCESS;
}
