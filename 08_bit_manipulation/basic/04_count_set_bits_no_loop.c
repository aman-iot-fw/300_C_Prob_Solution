#include<stdio.h>
#include<stdint.h>

uint8_t countSetBit(uint8_t reg){
  uint8_t count = 0;
  if(reg == 0)
    return 0;
  return 1 + countSetBit(reg & (reg - 1));
}

int main(){
  uint8_t reg = 128;
  printf("Count of set bit : %d", countSetBit(reg)  );
  return 0;
}

