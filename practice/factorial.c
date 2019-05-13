// The program refers to CS50
// GDB example provided by Nate Hardisson
// Calculate n! given user's input n

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // factorials aren't defined for the negative integers
    int num;
    do
    {
        printf("Enter a positive integer: ");
        num = GetInt();
    }
    while (num < 0);

    int factorial;
    for (int i = 1; i <= num; i++)
        factorial *= i;
        
    printf("%d! = %d\n", num, factorial);
    
    return 0;
}