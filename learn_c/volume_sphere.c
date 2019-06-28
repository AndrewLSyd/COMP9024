/* Program that takes the radius of a sphere and returns the volume */
#include <stdio.h>
// #include <gtk/gtk.h>
#include <math.h>
#define PI 3.1415
int
main(void){
    double radius, volume;
    printf("Please enter the radius of the sphere: ");
    scanf("%lf", &radius);
    printf("radius entered is %f", radius);
    volume = 4.0 / 3.0 * PI * pow(radius, 3);
    printf("the volume is %.2lf", volume);
    return 0; // main function typically returns 0 to indicate normal exit
}