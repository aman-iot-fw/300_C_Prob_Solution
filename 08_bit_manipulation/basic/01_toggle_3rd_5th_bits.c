#include<stdio.h>
#include<stdint.h>

uint8_t byte_ = 0b10100101; //165 in decimal

int main(){
    byte_ ^= (1<<3);
    // 0b10100101 XOR
    // 0b00001000
    // 0b10101101
    byte_ ^= (1<<5);
    // 0b10101101 XOR
    // 0b00100000
    // 0b10001101 

    printf("%d", byte_);
    //Output is 141 | 0b10001101 
    return 0;
}