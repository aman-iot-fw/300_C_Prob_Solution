/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t freq[256] = {0};

int main(){
    char *str = "Helloo";
    uint8_t len = strlen(str);

    for(uint8_t i = 0; i < len; i++){
        freq[str[i]]++;
    }
    printf("Duplicate char \n");
    for(uint8_t i = 0; i < 255; i++){
        if(freq[i]>1){
            printf("%c", i);
        }
    }
    return 0;
}

