// BSTsum.txt

//     Write an algorithm to recursively sum the elements of a BST rooted at Tree, where a Tree contains data, and pointers to its sub-trees left and right.
//     Convert your algorithm into C code by writing a function with signature:
//     Toggle line numbers

//        1  int sumTree(Tree t)

//     In the next question you can implement and test your function. 
// basic.c: insert nodes into a BST, print the tree and free all nodes
#include <stdio.h>
#include <stdlib.h>

typedef struct node *Tree;
struct node {
   int data;
   Tree left;
   Tree right;
};

// function prototypes
Tree insertTree (Tree, int);
Tree createTree (int);
void printTree(Tree t, int depth);
void freeTree   (Tree);
int sumTree(Tree t);
Tree revTree(Tree t);
Tree insertTreeRev(Tree t, int v);

int main(int argc, char ** argv) {
	Tree t = NULL;
	Tree tRev = NULL;

	// change to command line input
	printf("registers %d command line arguments\n", argc - 1);
	// loop across number of command line arguments (CLA)
	for (int CLA=1; CLA < argc; CLA++){
		// argv is a ptr to a bunch of char ptrs
		// if you dereference argv twice you get a char
		// char ** argv; *(argv) is a char ptr
		// *(argc + CLA) is a char *
		printf("reading into printf the char ptr: *(argv + %d) gives us %s\n", CLA, *(argv + CLA));
		printf("\tsame as reading into printf the char ptr: argv[%d] gives us %s\n", CLA, argv[CLA]);
		if (CLA == 1){  // for the first elemnt need to create try
			t = createTree(**(argv + CLA) - '0');  // implicit int casting
		}
		else {
			insertTree(t, **(argv + CLA) - '0');
		}
	}


   printTree(t, 0);
	printf("sum is %d\n", sumTree(t));
	
	tRev = revTree(t);
	printTree(tRev, 0);	
	printf("sum is %d\n", sumTree(tRev));

   putchar('\n');
   freeTree(t);
   return EXIT_SUCCESS;
}

Tree tRev = NULL;
Tree revTree(Tree t){
	// takes a tree in as an argument, reverses it (e.g. child that is greater or
	// equal to the parent is on the left instead of the right) and returns a tree
	// let's recursively travel through the tree, building a new reversed tree
	// as we go along

	if (t == NULL){
		return tRev;
	}
	if (tRev == NULL){  // first node
		tRev = createTree(t->data);
		revTree(t->left);
		revTree(t->right);
	}
	else {  // not first node, e.g. don't need to create tree
		insertTreeRev(tRev, t->data);
		revTree(t->left);
		revTree(t->right);
	}

	return tRev;
}

int sumTree(Tree t){
	// program that recursively sums a tree
	int sum=0;
	if (t == NULL){
		return sum;
	}
	else {
		sum += t-> data + sumTree(t->left) + sumTree(t->right);
	}
	return sum;
}

Tree insertTree(Tree t, int v) {
// binary search until NULL and then insert tree
   if (t == NULL) {  // (2) until NULL... then insert
      t = createTree(v);
   }
   else {  // (1) binary search 
      if (v < t->data) {
        t->left = insertTree (t->left, v);
      }
      else {
        t->right = insertTree (t->right, v);
      }
   }
   return t;
}

Tree insertTreeRev(Tree t, int v) {
// binary search until NULL and then insert tree
// REVERSE order
   if (t == NULL) {  // (2) until NULL... then insert
      t = createTree(v);
   }
   else {  // (1) binary search 
      if (v < t->data) {
        // t->left = insertTree (t->left, v);
		t->right = insertTreeRev (t->right, v);
      }
      else {
        // t->right = insertTree (t->right, v);
		t->left = insertTreeRev (t->left, v);
      }
   }
   return t;
}

Tree createTree (int v) {
   Tree t = NULL;

   t = malloc (sizeof(struct node));
   if (t == NULL) {
      fprintf(stderr, "Memory is exhausted: exiting\n");
      exit(1);
   }
   t->data = v;
   t->left = NULL;
   t->right = NULL;
   return t;
}

void printTree(Tree t, int depth) { // extra depth parameter
    if (t != NULL) {
        depth++;
        printTree (t->left, depth);
           for (int i=1; i<depth; i++){ // 'depth'*whitespace
              putchar('\t');
           }
           printf ("%d\n", t->data); // node to print
        printTree (t->right, depth);
    }
    return;
}

void freeTree(Tree t) { // free in postfix fashion
   if (t != NULL) {
      freeTree(t->left);
      freeTree(t->right);
      free(t);
   }
   return;
}

