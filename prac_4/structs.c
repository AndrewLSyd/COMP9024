// practice 4 structs
#include <stdlib.h>
#include <stdio.h>



int main(void){
	typedef
	// create a struct
		struct {
		   int   studentID;
		   int   age;
		   char  gender;
		   float WAM;
		}
	// typedef it to Person for resuse
	Person;

	Person per1; // initialise memory for per1, per2
	Person per2;
	Person *ptr; // initialise pointer to Person struct

	ptr = &per1; // ptr is pointing to per1
	per1.studentID = 3141592;
	ptr->gender = 'M'; // per1's gender has been assigned to M
	ptr = &per2; // ptr is now pointing to per2
	ptr->studentID = 2718281; // change per2's studentID
	ptr->gender = 'F'; // chnge per2's gender
	per1.age = 25; //change per1's age
	per2.age = 24; // change per2's age
	ptr = &per1; // ptr is pointing to per1 again
	per2.WAM = 86.0; // change per2's WAM
	ptr->WAM = 72.625; // change per1's WAM
	// per1.studentID = 3141592
	// per1.age = 25
	// per1.gender = 'M'
	// per1.WAM = 72.625
	// per2.studentID = 2718281
	// per2.age = 24
	// per2.gender = 'F'
	// per2.WAM = 86.0
	return EXIT_SUCCESS;
}
