#include<stdio.h>
#include<stdlib.h>
#include<time.h>

unsigned long long int fibo(unsigned long long int n);

int main(int argc, char* argv[])
{
    unsigned long long int rs;
    time_t start, end, delta;

    if(argc != 2)
    {
        printf("Argc not found");
        exit(EXIT_SUCCESS);
    }
    start = time(0);
    rs = fibo(atoi(argv[1]));
    end = time(0);
    printf("Fibonacii term %llu \n", rs);
    printf("Delta = %lld\n", end-start );
}
unsigned long long int fibo(unsigned long long int n)
{
    unsigned long long int rs;

    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    
    return (fibo(n-1) + fibo(n-2));
}