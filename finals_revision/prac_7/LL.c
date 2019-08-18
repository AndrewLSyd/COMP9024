/*
  LL.c
  an ADT for a linked list
 */

#include "LL.h"
#include <limits.h>

struct node {
  int data;
  struct node *next;
};

List createList(void) { // creates a node, fills with INT_MAX and NULL
   List marker;
   marker = malloc(sizeof(struct node));
   if (marker == NULL) {
       fprintf (stderr, "createList: no memory, aborting\n");
       exit(1);
   }
   marker->data = INT_MAX;         // defined in <limits.h>
   marker->next = NULL;
   return marker;
}

void putTail(int n, List marker) { // add new data to the tail
   if (marker == NULL) {
       fprintf (stderr, "putTail: no linked list found\n");
   }
   else {
       List new = createList();   // re-use of createList to make a node
       new->data = n;             // overwrites INT_MAX with proper data
       List p = marker;
       while (p->next != NULL) {  // find the last node 
           p = p->next;
       }
       p->next = new;             // append new to the list
   }
   return;
}

void putHead(int n, List marker) { // insert at the head
   if (marker == NULL) {
       fprintf (stderr, "putTail: no linked list found\n");
   }
   else {
        List new = createList();   // re-use of createList to make a node
        new->data = n;             // overwrites INT_MAX with proper data
		new->next = marker->next;
		marker->next = new;
   }
   return;
}

int getTail(List marker) {         // get & delete last node
	int retval = 0;
   if (marker == NULL) {
       fprintf (stderr, "putTail: no linked list found\n");
   }
	else if (marker->next == NULL){
	fprintf(stderr, "error, list is empty"); // when list is empty
	}
   else {
		// traverse to the end
       List p = marker;
		
       while ((p->next)->next != NULL) {  // find the 2nd last node 
           p = p->next;
       }
		// p is now the 2nd last node from the end
		retval = (p->next)->data;  // get data from last node
		// delete last node and cleanup
		free(p->next);
		p->next = NULL;

   }
   return retval;
}

int getHead(List marker) {         // get & delete head node
	int retval = 0;
   if (marker == NULL) {
       fprintf (stderr, "putTail: no linked list found\n");
   }
	else if (marker->next == NULL){
	fprintf(stderr, "error, list is empty"); // when list is empty
	}
   else {
		// traverse to the end
       List p = marker->next;  // temp saving for clean-up after
		
		retval = (marker->next)->data;  // get data from first non-marker node

		// link marker to 2nd non-marker node		
		marker->next = (marker->next)->next;

		// delete last node and cleanup
		free(p);
		p = NULL;

   }
   return retval;
}

int isEmptyList(List marker) {     // 0 is false, 1 is true
   int empty = 0;
   if (marker == NULL) {
       fprintf (stderr, "isEmptyList: no linked list found\n");
   }
   else {
       empty = marker->next == NULL;
   }
   return empty;
}

void showList(List marker) {
   if (marker == NULL) {
      fprintf(stderr, "showList: no linked list found\n");
   }
   else {
       printf("List: ");
       if (marker->next == NULL) {
          printf("<< >>\n");
       }
       else {
          printf("<<");              // start with <<
          List p = marker->next;     // get the head
          while (p->next != NULL) {
             printf("%d, ", p->data); // print each element
             p = p->next;
          }
          printf("%d>>\n", p->data); // last element + >>
       }
   }
   return;
}
