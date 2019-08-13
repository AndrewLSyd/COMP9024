// struct representing opal card
// Define a data type to store all the information of a single ride with the Opal card. Here are 3 sample records. 
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    // char day_of_wk[10];
    int year, month, day, hour, min; // 24 hour time
} date_t;

typedef char namestr_t[32];

typedef struct{
    int tran_num;
    date_t date;
    char mode;
    namestr_t details;
    int journey_no;
    namestr_t fare_applied;

} opal_t;

int main(void){
    opal_t OPAL = {123, {2019, 6, 1, 12, 12}, 'B', "blah", 2, "hello"};
    printf("%d %d %d\n", OPAL.tran_num, OPAL.date.year, OPAL.date.month);

    printf("address of OPAL.tran_num is %p\n", &OPAL.tran_num);
    printf("address of OPAL.tran_num is %p\n", &OPAL.fare_applied[31]);
    // an unsigned long is a long without a sign - you can effectively capture an int
    // of twice the size (as the space isn't used for negative ints)
    printf("address of OPAL.tran_num is %lu\n", sizeof(opal_t));
    int my_int;
    printf("bytes of int %lu\n", sizeof(my_int));
    date_t my_date;
    printf("bytes of date_t %lu as it has four ints \n", sizeof(my_date));
    char my_char;
    printf("bytes of char %lu\n", sizeof(my_char));
    printf("opal size below\n");
    printf("bytes of OPAL.tran_num %lu, as it is an int\n", sizeof(OPAL.tran_num));
    printf("bytes of OPAL.date %lu, as it has 5 ints\n", sizeof(OPAL.date));
    printf("bytes of OPAL.mode %lu, as it is one char\n", sizeof(OPAL.mode));
    printf("bytes of OPAL.details %lu, as it is 32 chars\n", sizeof(OPAL.details));
    printf("bytes of OPAL.journey_no %lu, as it is an int\n", sizeof(OPAL.journey_no));
    printf("bytes of OPAL.fare_applied %lu\n", sizeof(OPAL.fare_applied));
    printf("bytes of OPAL %lu (padding involved)\n", sizeof(OPAL));


    return EXIT_SUCCESS;
}
