#include <stdio.h>

char str1[20] = "Hello";
char *str2 = "World";

void concatenate(char *str1, char *str2){
    while(*str1){
        str1++;
    }
    *str1 = ' ';
    str1++;
    while(*str2){
        *str1 = *str2;
        
        str1++;
        str2++;
    }
    
    *str1 = '\0';
}

int main()
{
    concatenate(str1, str2);
    printf("%s", str1);

    return 0;
}
