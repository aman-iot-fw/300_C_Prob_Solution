#include<stdio.h>
#include<stdint.h>

uint8_t value = 0b01010111;

int main(){
  int count = 0;
  while(value){
    value &= (value - 1);
    count++;
  }
printf("%d", count);
}
