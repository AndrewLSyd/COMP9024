//pointers.txt
#include <stdio.h>
#include <stdlib.h>

int nums[12] = {5,3,6, 2,7, 4, 9, 1, 8};

int main(void){
	printf("the address of nums, %p\n", &nums[0]);
	printf("the size of each element in the array is %lu\n bytes", sizeof(nums[0]));
	printf("a. the address of nums + 4 should be an address 4 ahead of nums, %p\n", nums + 4);
	printf("b. the value of *num + 4 is %d\n", *nums + 4);
	printf("c. the value of *(nums + 4) should be the 5th element of the array, %d\n", *(nums + 4));
	printf("d. the value of nums[4] should be the 5th element of the array, %d\n",  nums[4]);
	printf("e. the value of *(nums + *(nums + 3)) is the 3rd element of the array, %d\n",  *(nums + *(nums + 3)));
	return EXIT_SUCCESS;

}
