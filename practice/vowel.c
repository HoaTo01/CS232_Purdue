#include <stdio.h>
#include <stdlib.h>

void nextVowel(char c)
{
    while(!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'))
    {
        c++;
    }
}
main()
{
    while(1)
    {
        int c = getchar();
        if(c == EOF || c == '\n')
            return;
        nextVowel(c);
        putchar(c);
    }
}