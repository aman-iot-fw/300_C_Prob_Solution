#include <stdio.h>
#include <stdint.h>

uin8t_t reg = 0b11011010;

void isolateRightMostBit(uint8_t reg){
  uint8_t isolated = reg;
  isolated &= (~reg + 1);
  printf("%08b", isolated);
}

int main(){
  isolateRightMostBit(reg);
  return 0;
}
