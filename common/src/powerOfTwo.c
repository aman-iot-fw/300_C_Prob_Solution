#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

bool isPowOfTwo(int value){
  return ((value > 0) && (value & (value-1)) == 0);
}

int main(){

  int value = 1024;
  if(isPowOfTwo(value))
    printf("Input is Power of Two");

  else
    printf("Input is not power of Two");
}
