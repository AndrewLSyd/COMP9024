// quackLL.c: a linked-list-based implementation of a quack
#include "quack.h"
#include <limits.h>

#define HEAD_DATA INT_MAX // dummy data

struct node {
   int data;
   struct node *next;
};

Quack createQuack(void) { // returns a head node
   Quack head;
   head = malloc(sizeof(struct node));
   if (head == NULL) {
      fprintf (stderr, "createQuack: no memory, aborting\n");
      exit(1);
   }
   head->data = HEAD_DATA; // should never be used
   head->next = NULL;
   return head;
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
      // insert the newnode at the head
      newnode->data = data;       // assign the data
      newnode->next = qs->next;   // link to 'old' linked list
      qs->next = newnode;         // make it the head
   }
   return;
}

void qush(int data, Quack qs) {
	puts("=== we are qushing! ===\n");
	// Step 0: Create new node
	Quack newnode = NULL;  // Quack is a pointer to a node
	newnode = malloc(sizeof(struct node));
	if (newnode == NULL){
		fprintf(stderr, "not enough memory");
		exit(EXIT_FAILURE);
	}
	newnode->data = data;
	newnode->next = NULL;
	printf("newnode->data = %c\n", newnode->data);

	// Step 1: traverse to the end of the stack
	Quack last_node_ptr = qs;
	while (last_node_ptr->next != NULL){
		if (last_node_ptr->data != INT_MAX){
			printf("traversing... %c\n", last_node_ptr->data);
		}
		last_node_ptr = last_node_ptr->next;
	}

	// put at end of the stack, back patching
	printf("adding to last node in linked list... %c\n", newnode->data);
	last_node_ptr->next = newnode;
	
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
         retval = topnode->data;   // grab the data
         qs->next = topnode->next; // remove the head
         free(topnode);            // clean up
      }
   }
   return retval;
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
      if (qs->data != HEAD_DATA) {
         fprintf(stderr, "showQuack: linked list head corrupted\n");
      }
      else {
         printf("Quack: ");
         if (qs->next == NULL) {
            printf("<< >>\n");
         }
         else {
            printf("<<");                 // start with <<
            qs = qs->next;                // step over the head link
            while (qs->next != NULL) {
               printf("%d, ", qs->data);  // print each element
               qs = qs->next;
            }
            printf("%d>>\n", qs->data);    // last element ends with >>
         }
      }
   }
   return;
}

