 
#include<stdio.h>
#include<string.h>
void main()
{
    int i=0;
    char arr1[ 20 ] = "Trumantiger";
    char arr2[ 20 ];
    while(i<20){
        arr2[ i ] = arr1[i];
	++i;
    }
    strcpy( arr1 , arr2 );
    printf("%s\n",arr1);
}
