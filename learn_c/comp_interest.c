/* Program that calculates compound interestlogs */
#include <stdio.h>
#include <math.h>


int
main(void){
    int year, rate, month;
    double balance=0;
    printf("Monthly savings of $100, with monthly compounded interest.\n");
    printf("Annual rate   |     2%%   |   3%%   |   4%%   |   5%%   |   6%%   |   7%%   \n");
    for (year = 1; year < 8; year++){
        printf("After %d years |", year);
        for (rate = 2; rate < 8; rate ++){
            balance = 0;

            for (month = 1; month <= year * 12; month ++){                
                // printf("%lf", (1 + (double)rate / 100 / 12));
                balance *= (1.0 + rate / 100.0 / 12.0);
                balance += 100;
                // printf("month %d: balance %.2lf", month, balance);
            }
            printf(" %7.0lf ", balance);
        }
        printf("\n");
    }

}