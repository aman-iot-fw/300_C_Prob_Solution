#include <stdio.h>

void converToLowerCase(char *inp){
    char *start = inp;
    while(*inp != '\0'){
        if(*inp >= 'A' && *inp <= 'Z'){
            *inp += 32;
        }
        inp++;
    }
    printf("%s", start);
}

int main()
{
    char str[] = "HeLlo";
    converToLowerCase(str);
    

    return 0;
}
