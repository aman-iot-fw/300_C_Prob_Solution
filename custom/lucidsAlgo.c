/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STACK_WORD 5

//Lucid's algorithm 
//greatest common divisor
int gcd(int a, int b){
    while(b){
        int t = b;// gcd(a,b) = gcd(b, a % b), gcd(48, 18) = gcd(18, 48 %18) = gcd( 18, 12)
        b = a % b;// gcd(12, 18 % 12) = gcd(12, 6) = (6, 12 % 6) = gcd(6, 6 % 6) = gcd(0, 6 % 0) 
        a = t;
    }
    return a;
}


int main()
{
    printf("%d", gcd(18,48));

    return 0;
}
