#include <stdio.h>
#include <string.h>
#include <stdint.h>

char *str = "Listen to your instinct";

uint8_t freq[256] = {0};

int main()
{
    int len = strlen(str);

    for(int i = 0; i < len; i++)
    {
        if((str[i] >= 'a' && str[i] <= 'z') ||
           (str[i] >= 'A' && str[i] <= 'Z'))
        {
            freq[(unsigned char)str[i]]++;
        }
    }

    int maxCount = 0;
    unsigned char maxChar = 0;

    for(int i = 0; i < 256; i++)
    {
        if(freq[i] > maxCount)
        {
            maxCount = freq[i];
            maxChar = i;
        }
    }

    printf("Max occurring char : %c, Count : %d\n",
           maxChar,
           maxCount);

    return 0;
}
