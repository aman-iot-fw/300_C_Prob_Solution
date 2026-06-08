#include<stdio.h>
#include<stdint.h>

int removeDup(int arr[], int size){
  uint8_t seen[256] = {0};
  int write = 0;
  for(int i = 0; i < size; i++){
    if(!seen[arr[i]]){
      seen[arr[i]] = 1;
      arr[write] = arr[i];
      write++;
    }
  }
  return write;
}

int main(){
  int arr[] = {1, 1, 2, 3, 5, 3, 5, 6, 7, 8, 1};  
  int size = sizeof arr/ sizeof arr[0];
  int newSize = removeDup(arr, size);

  for(int i = 0; i < newSize; i++){
    printf("%d ", arr[i]);
  }
  return 0;
}
