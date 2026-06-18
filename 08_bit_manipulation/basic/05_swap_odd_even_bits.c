#include<stdio.h>
#include<stdint.h>

uint8_t swapOddEven(uint8_t reg){
    uint8_t oddBits  = reg & 0b10101010;
    uint8_t evenBits = reg & 0b01010101;
    
    oddBits  >>= 1;
    evenBits <<= 1;
    
  return oddBits | evenBits;
}

int main(){
  uint8_t reg = 0b10001011;
  printf("Swaped Bits : %08b", swapOddEven(reg));
  return 0;
}

