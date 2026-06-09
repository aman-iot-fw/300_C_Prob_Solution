#include<stdio.h>
#include<stdint.h>

void sortArr(int arr[], int size){
  for(int i = 0; i < size; i++){
    for(int j = i; j < size; j++){  
        if(arr[i] > arr[j]){
          int tmp = arr[i];
          arr[i] = arr[j];
          arr[j] = tmp;
        }
    }
  }
}

void findKthMinMax(int arr[], int size, int k){
  sortArr(arr, size);
  printf("Kth Min : %d\n", arr[k - 1]);
  printf("Kth Max : %d", arr[size - k]);
}

int main(){
  int arr[] = {1, 6,8,2,5,0,7,3,4};
  int size = sizeof arr/ sizeof arr[0];
  findKthMinMax(arr, size, 3);
  return 0;
}
