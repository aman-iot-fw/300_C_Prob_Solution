#include<stdio.h>

int firstSetBit(int n){
  int pos = 1;
  while(!(n & 1)){
    n >>= 1;
    pos++;
  }
return pos;
}

int main(){
  int value = 16;
  printf("%d", firstSetBit(value));

return 0;
}

