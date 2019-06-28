/* Program that calculates taxes */
#include <stdio.h>
#include <math.h>
#define PI 3.1415
int
main(void){
    double gross_income, tax, medicare_levy;
    printf("Please enter your gross income: ");
    scanf("%lf", &gross_income);
    printf("You have entered in %.2lf as your gross income.", gross_income);
    if (gross_income < 18200) tax = 0;
    else if (gross_income < 37000) tax = (gross_income - 18200) * 0.19;
    else if (gross_income < 80000) tax = (37000 - 18200) * 0.19 + (gross_income - 37000) * 0.325;
    else if (gross_income < 180000) tax = (37000 - 18200) * 0.19 + (80000 - 37000) * 0.325 + (gross_income - 80000) * 0.37;
    else tax = (37000 - 18200) * 0.19 + (80000 - 37000) * 0.325 + (180000 - 80000) * 0.37 + (gross_income - 180000) * 0.45;
    /* medicare levy*/
    printf("Your tax estimate ex medicare is %.2lf", tax); 

    medicare_levy = gross_income * 0.015;
    printf("Your tax estimate inc medicare levy is %.2lf", medicare_levy);
    return 0;
}