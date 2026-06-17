#include <stdio.h>

void trimWhitespace(char *str)
{
    char *start = str;
    char *end = str;

    /* Find first non-space */
    while(*start == ' ')
        start++;

    while(*end)
        end++;

    end--;

    while(end > start && *end == ' ')
        end--;

    char *dst = str;

    while(start <= end)
    {
        *dst++ = *start++;
    }

    *dst = '\0';
}

int main()
{
    char str[] = "   Hello World   ";

    trimWhitespace(str);

    printf("%s\n", str);

    return 0;
}
