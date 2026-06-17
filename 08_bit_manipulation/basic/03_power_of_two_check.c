#include<stdio.h>
#include<stdint.h>

uint8_t powOfTwo(uint8_t reg){
  return ((reg > 0) && (reg & reg - 1) == 0);
}

int main(){
  uint8_t reg = 128;
  powOfTwo(reg) ? printf("Number is power of two") : printf("Number is not power of two");
  return 0;
}
