/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>

#define SIZE_OF_STACK 4

typedef struct bytePack{
    int data[SIZE_OF_STACK];
    uint8_t byteOffset;
    uint8_t wordTop;
}bytePack_t;

void initStack(bytePack_t *s){
    for(int i = 0; i < SIZE_OF_STACK; i++){
        s->data[i] = 0;
    }
    s->byteOffset = 0;
    s->wordTop = 0;
}

int pushStack(bytePack_t *s, uint8_t value){
    if(s->wordTop >= SIZE_OF_STACK){
        return -1;
    }
    
    s->data[s->wordTop] |= ((int)value << (s->byteOffset * 8));
    s->byteOffset++;
    
    if(s->byteOffset == 4){
        s->byteOffset = 0;
        s->wordTop+=1;
    }
    
    return 0;
}

void printStack(bytePack_t *s){
    for(int i = 0; i < SIZE_OF_STACK; i++){
        printf("Word : %d, Data 0x%08x\n", i, s->data[i]);
    }
}

int main()
{
    bytePack_t s;
    
    initStack(&s);
    
    pushStack(&s, 0x01);
    pushStack(&s, 0x02);
    pushStack(&s, 0x03);
    pushStack(&s, 0x04);
    pushStack(&s, 0x05);
    pushStack(&s, 0x06);
    pushStack(&s, 0x07);
    pushStack(&s, 0x08);
    pushStack(&s, 0x09);
    pushStack(&s, 0x0A);
    pushStack(&s, 0x0B);
    pushStack(&s, 0x0C);
    pushStack(&s, 0x0D);
    
    printStack(&s);

    return 0;
}
