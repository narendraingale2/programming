#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[])
{
    int n;
   if(argc == 2)
   {
    n = atoi(argv[1]);
    if(n%2 == 0)
        printf("This is even number");
    else
        printf("This is odd number");
   } 
}