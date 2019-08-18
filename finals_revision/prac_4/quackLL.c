// QuackLL.c: a linked-list-based implementation of a quack
#include "Quack.h"
#include "limits.h"

#define MARKERDATA INT_MAX // dummy data

struct node {
   int data;
   struct node *next;
};

Quack createQuack(void) {
   Quack marker;
   marker = malloc(sizeof(struct node));
   if (marker == NULL) {
      fprintf (stderr, "createQuack: no memory, aborting\n");
      exit(1);
   }
   marker->data = MARKERDATA; // should never be used
   marker->next = NULL;
   return marker;
}

void push(int data, Quack qs) {
   Quack newnode;
   if (qs == NULL) {
      fprintf(stderr, "push: quack not initialised\n");
   }
   else {
      newnode = malloc(sizeof(struct node));
      if (newnode == NULL) {
         fprintf(stderr, "push: no memory, aborting\n");
         exit(1);
      }
      newnode->data = data;
      newnode->next = qs->next;
      qs->next = newnode;
   }
   return;
}

void qush(int data, Quack qs) {
	// instead of adding a node to the 2nd node (after the marker/head node)
	// for our qush we need to traverse the list and add it to the end
   Quack newnode;
	Quack node_tmp;  // Quack is a pointer to a node

   if (qs == NULL) {
      fprintf(stderr, "push: quack not initialised\n");
   }
   else {
      newnode = malloc(sizeof(struct node));
      if (newnode == NULL) {
         fprintf(stderr, "push: no memory, aborting\n");
         exit(1);
      }
      newnode->data = data;
		nownode->next = NULL;  // just in case set this to NULL as it's the end of the list
	
		// traverse to the end of the list
		node_tmp = qs;  //  set it to the marker at first
		while (node_tmp->next != NULL){
			node_tmp = node_tmp->next;
		}
		// now node_tmp-> == NULL
		// now that we are at the end of the node we can attach our new node
		node_tmp->next = newnode;  // point it to our new node
   }
   return;
}

int pop(Quack qs) {
   int retval = 0;
   if (qs == NULL) {
      fprintf(stderr, "pop: quack not initialised\n");
   }
   else {
      if (isEmptyQuack(qs)) {
         fprintf(stderr, "pop: quack underflow\n");
      }
      else {
         Quack topnode = qs->next; // top dummy node is always there
         retval = topnode->data;
         qs->next = topnode->next;
         free(topnode);
      }
   }
   return retval;
}

Quack destroyQuack(Quack qs) { // remove the Quack  and returns NULL
   if (qs == NULL) {
      fprintf(stderr, "destroyQuack: quack not initialised\n");
   }
   else {
      Quack ptr = qs->next;
      while (ptr != NULL) {
         Quack tmp = ptr->next;
         free(ptr);
         ptr = tmp;
      }
      free(qs);
   }
   return NULL;
}

void makeEmptyQuack(Quack qs) {
   if (qs == NULL)
      fprintf(stderr, "makeEmptyQuack: quack not initialised\n");
   else {
      while (!isEmptyQuack(qs)) {
         pop(qs);
      }
   }
   return;
}

int isEmptyQuack(Quack qs) {
   int empty = 0;
   if (qs == NULL) {
      fprintf(stderr, "isEmptyQuack: quack not initialised\n");
   }
   else {
      empty = qs->next == NULL;
   }
   return empty;
}

void showQuack(Quack qs) {
   if (qs == NULL) {
      fprintf(stderr, "showQuack: quack not initialised\n");
   }
   else {
      printf("Quack: ");
      if (qs->next == NULL) {
         printf("<< >>\n");
      }
      else {
         printf("<<");                 // start with <<
         qs = qs->next;                // step over the marker link
         while (qs->next != NULL) {
            printf("%d, ", qs->data);  // print each element
            qs = qs->next;
         }
         printf("%d>>\n", qs->data);    // last element ends with >>
      }
   }
   return;
}
