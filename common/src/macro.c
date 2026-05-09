#include <stdio.h>
#include <stdint.h>
#include "main.h"

#define TOGGLE(REGISTER, POSITION) REGISTER ^ (1 << POSITION)
#define SETBIT(REGISTER, POSITION) REGISTER |= (1 << POSITION)
#define CLEARBIT(REGISTER, POSITION) REGISTER &= ~(1 << POSITION)

#define GREATER(A, B) (A > B ? A : B)


int main()
{
    uint8_t a = 0;
    printf("%d",GREATER(1, 7));

    return 0;
}
