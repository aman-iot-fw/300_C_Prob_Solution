#include <stdio.h>

// what will be the output, and why?

void send(int *buf)
{
    int len = sizeof(buf) / sizeof(buf[0]);
    printf("Length = %d\n", len);
}

int main(void)
{
    int data[10] = {0};
    send(data);
    return 0;
}
