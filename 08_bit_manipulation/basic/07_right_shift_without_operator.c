#include<stdio.h>
#include<stdint.h>

uint8_t rtSftWithoutOper(uint8_t reg, uint8_t pos){
  //righ shift is equal to divide by 2
  //left shift is equal to multiply by 2

 return reg / pos / 2;
}

int main(){
  uint8_t reg = 0b00010100;
  printf("%08b", rtSftWithoutOper(reg, 1));
}
