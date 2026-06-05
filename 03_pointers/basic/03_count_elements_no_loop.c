#include<stdio.h>
#include<stdint.h>

int arr[] = {1,2,3,4,5,6};

int countElement(int *arr){
  int *base = arr;
  int elementSize = (uint8_t)(base + 1) - (uint8_t)base;
  printf("%d\n", elementSize);
  return 0;
}

int main(){
  countElement(arr);
  return 0;
}
