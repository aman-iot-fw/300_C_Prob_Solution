#include<stdio.h>

int nonRepInArr(int arr[], int size){
  int result = 0;
  for(int i = 0; i < size; i++){
    result ^= arr[i];
  }
  return result;
}

int main(){
  int arr[] = {1,1,2,2,3,3,4,5,5,6,6};
  int size = sizeof arr / sizeof arr[0];
  printf("Non Repetative Number In The Array : %d",nonRepInArr(arr, size));

  return 0;
}
