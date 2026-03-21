#include<stdio.h>

unsigned int reverse(unsigned int n){
    unsigned int rev = 0;
    for(int i = 0; i < 32; i++){
        rev <<= 1;
        rev |= (n & 1);
        n >>= 1;
    }
    return rev;
}

int main(){
  int value = 133;
  printf("%08b", value);
  printf("\n%08b", reverse(value));

return 0;
}


