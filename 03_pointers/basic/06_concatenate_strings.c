/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
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
