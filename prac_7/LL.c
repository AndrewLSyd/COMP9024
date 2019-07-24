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
   List marker;  // List is a pointer to a node
   marker = malloc(sizeof(struct node));
   if (marker == NULL) {
       fprintf (stderr, "createList: no memory, aborting\n");
       exit(1);
   }
   marker->data = INT_MAX;         // defined in <limits.h>
   marker->next = NULL;
   return marker;  // returns pointer to a node
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
       fprintf (stderr, "putHead: no linked list found\n");
   }
   else {
       List new = createList();   // re-use of createList to make a node
       new->data = n;             // overwrites INT_MAX with proper data
		// new->next needs to point to marker->next	
		new->next = marker->next;
		// marker->next needs to point to new list
		marker->next = new;       
   }
   return;
}

int getTail(List marker) {         // get & delete last node
	int out=INT_MAX;
   if (marker == NULL) {
       fprintf (stderr, "getTail: no linked list found\n");
   }
   else {
		// traverse to 2nd last node of linked list
       List p = marker;
       while ((p->next)->next != NULL) {  // find the last node 
           p = p->next;
       }

       out = (p->next)->data;

		//clean-up
		free(p->next);
		p->next = NULL;
   }
   return out;
}

int getHead(List marker) {         // get & delete head node
	int temp_int=INT_MAX;
	void * temp;
   if (marker == NULL) {
       fprintf (stderr, "getHead: no linked list found\n");
   }
   else {
		// save next node as temp	
		temp_int = (marker->next)->data;
		temp = marker->next;
		// set marker to next next node
		marker->next = (marker->next)->next;
		// clean-up
		free(temp);
		temp = NULL;
   }
   return temp_int;
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
