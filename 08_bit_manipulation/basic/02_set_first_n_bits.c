#include<stdio.h>
#include<stdint.h>

uint8_t setNbits(uint8_t inp, uint8_t n){
    if(n > 8){
      n = 8;  
    } 
    if(n == 0){
      return inp;  
    } 
    uint8_t mask = (1u << n) - 1;
    return inp |= mask;
}

int main(){
    uint8_t oneByte = 0b00000000;
    printf("%u (Binary 0b%08b)", setNbits(oneByte, 2),setNbits(oneByte, 2));
    return 0;
}