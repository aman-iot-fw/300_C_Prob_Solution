#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct List
{
    int data;
    struct List *Next;
};

int main(){

    printf("%d", sizeof(struct List));

    return 0;
}
