#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int check_palindrom(char* str_to_check);
int str_length(char str[]);

int main(int argc, char* argv[])
{
    int i, j;
    int is_palindrom;
    is_palindrom = 0;
    
    if(argc == 2)
    {
       is_palindrom = check_palindrom(argv[1]);
       if(is_palindrom == 1)
        printf("This is palindrom");
       else
        printf("This is not palindrom");
    }
}

int str_length(char str[]) 
{
    int count;

    for(count = 0; str[count] != '\0'; count++);

    return count;
}

int check_palindrom(char* str_to_check)
{
    int i, j;
    j = str_length(str_to_check) - 1;
    i = 0;
    while ( i < j)
    {
        if(str_to_check[i] != str_to_check[j])
            return 0;
        i++;
        j--;
        
    }
    
    return 1;
}