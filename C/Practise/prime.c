#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[])
{
    int n;
    int i, is_prime=1;

   if(argc == 2)
   {
    n = atoi(argv[1]);
    if(n%2 == 0)
        printf("This is even number\n");
    else
        printf("This is odd number\n");
    
    for(i = 2; i<n; i++)
    {
        if(n%i == 0 )
        {
            is_prime = 0;
            break;
        }
    }

    if(is_prime == 1)
        printf("Number is prime\n");
    else
        printf("Number is not prime\n");
   } 
}