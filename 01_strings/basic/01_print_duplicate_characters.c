<<<<<<< HEAD
/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
=======
>>>>>>> 27cc6539fa3eaa2f26e97b7f01ea083fcd315066
#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t freq[256] = {0};
<<<<<<< HEAD

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
=======
char *str = "Helloo";

int main(){
    uint8_t len = strlen(str);
    
    for(uint8_t i = 0; i < len; i++){
        freq[str[i]]++;
    }

    for(uint8_t i = 0; i < 255; i++){
        if(freq[i] > 1){
            printf("%c ", i);
>>>>>>> 27cc6539fa3eaa2f26e97b7f01ea083fcd315066
        }
    }
    return 0;
}
<<<<<<< HEAD

=======
>>>>>>> 27cc6539fa3eaa2f26e97b7f01ea083fcd315066
