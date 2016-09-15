
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.14

int main(void)
{
int r;
printf("Select a radius to calculate the area of a circle for:\n");
scanf("%d",&r);

float area;

area=pow(r,2)*pi;

printf("the area of the circle is %.2f.\n",area);
printf("this is the first change\n");
return 0;
}
