#include <stdio.h>
#include <stdint.h>

int main(){
    long int data;

    size_t size= (uint8_t *)(&data + 1) - (uint8_t *)(&data);

    printf("Sizeof the datatype is : %d\n", size);

    return 0;
}
