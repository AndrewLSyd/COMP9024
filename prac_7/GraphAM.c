// GraphAM.c: an adjacency matrix implementation

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

struct graphRep { 
    int nV;       // #vertices 
    int nE;       // #edges 
    int **edges;  // matrix of Booleans ... THIS IS THE ADJACENCY MATRIX
};

Graph newGraph(int numVertices) { 
    Graph g = NULL;
    if (numVertices < 0) {
       fprintf(stderr, "newgraph: invalid number of vertices\n");
    }
    else {
        g = malloc(sizeof(struct graphRep));
        if (g == NULL) {
            fprintf(stderr, "newGraph: out of memory\n");
            exit(1);
        }
        g->edges = malloc(numVertices * sizeof(int *)); 
        if (g->edges == NULL) {
            fprintf(stderr, "newGraph: out of memory\n");
            exit(1);
        }
        int v; 
        for (v = 0; v < numVertices; v++) { 
            g->edges[v] = malloc(numVertices * sizeof(int)); 
            if (g->edges[v] == NULL) {
                fprintf(stderr, "newGraph: out of memory\n");
                exit(1);
            }
            for (int j = 0; j < numVertices; j++) {
                g->edges[v][j] = 0;
            }
        } 
        g->nV = numVertices; 
        g->nE = 0; 
    }
    return g;
}

Graph freeGraph(Graph g) {
	// each malloc must be freed
	// free arrays, rows in adjacency matrix g->edges[i]
    for (int v = 0; v < g->nV; v++) { 
        free(g->edges[v]);
    } 
	// free array of pointers to arrays, free entire matrix
	free(g->edges);
	// free graph
	free(g);
	return g;
}

void showGraph(Graph g) { // print a graph
    if (g == NULL) {
        printf("NULL graph\n");
    }
    else {
        printf("V=%d, E=%d\n", g->nV, g->nE); 
        int i;
        for (i = 0; i < g->nV; i++) { 
            int nshown = 0; 
            int j;
            for (j = 0; j < g->nV; j++) { 
                if (g->edges[i][j] != 0) { 
                    printf("<%d %d> ", i, j);
                    nshown++;
                }
            }
            if (nshown > 0) {
                printf("\n");
            }
        }
    }
    return;
}

static int validV(Graph g, Vertex v) { // checks if v is in graph 
    return (v >= 0 && v < g->nV); 
}

Edge newE(Vertex v, Vertex w) { // create an edge from v to w 
    Edge e = {v, w};
    return e; 
} 
void showE(Edge e) { // print an edge
    printf("<%d %d>", e.v, e.w);
    return; 
} 

int isEdge(Graph g, Edge e) { // return 1 if edge found, otherwise 0
	return g->edges[e.v][e.w];
}

void insertE(Graph g, Edge e) { // insert an edge into a graph 
   if (g == NULL) {
      fprintf(stderr, "insertE: graph not initialised\n");
   }
   else {
       if (!validV(g, e.v) || !validV(g, e.w)) {
          fprintf(stderr, "insertE: invalid vertices <%d %d>\n", e.v, e.w);
       }
       else {
          if (isEdge(g, e) == 0) { // increment nE only if it is new
             g->nE++; 
          }
          g->edges[e.v][e.w] = 1; 
          g->edges[e.w][e.v] = 1; 
       }
   }
   return;
} 

void removeE(Graph g, Edge e) { // remove an edge from a graph 
    if (g == NULL) {
        fprintf(stderr, "removeE: graph not initialised\n");
    }
    else {
        if (!validV(g, e.v) || !validV(g, e.w)) {
            fprintf(stderr, "removeE: invalid vertices\n");
        }
        else {
            if (isEdge(g, e) == 1) {   // is edge there?
                g->edges[e.v][e.w] = 0; 
                g->edges[e.w][e.v] = 0; 
                g->nE--; 
            }
        }
    }
    return;
} 
