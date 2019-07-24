// Graph.h: ADT interface for undirected/unweighted graphs

typedef int Vertex;               // define a VERTEX

typedef struct {                  // define an EDGE
  Vertex v;
  Vertex w;
} Edge;

typedef struct graphRep *Graph;   // define a GRAPH

Graph newGraph(int);              // create a new graph
Graph freeGraph(Graph);            // free the graph mallocs
void showGraph(Graph);            // print the graph

Edge newE(Vertex, Vertex);        // create a new edge
void insertE(Graph, Edge);        // insert an edge
void removeE(Graph, Edge);        // remove an edge
void showE(Edge);                 // print an edge
int isEdge(Graph, Edge);          // check edge exists

