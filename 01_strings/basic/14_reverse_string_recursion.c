#include <stdio.h>

void reverseWords(char *str)
{
    if(*str == '\0')
        return;

    char *space = str;

    while(*space && *space != ' ')
        space++;

    if(*space)
    {
        reverseWords(space + 1);
        printf("%.*s ", (int)(space - str), str);
    }
    else
    {
        printf("%s ", str);
    }
}

int main()
{
    char str[] = "hey how are you";

    reverseWords(str);

    return 0;
}
