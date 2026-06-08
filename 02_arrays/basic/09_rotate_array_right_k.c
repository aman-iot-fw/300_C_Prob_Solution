#include<stdio.h>
#include<stdint.h>

void rev(int arr[], int left, int right){
    while(left < right){
        int tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;
        
        left++;
        right--;
    }
}

void rotateArrRightK(int arr[], int size, int k){
    rev(arr, 0, size - 1);
    rev(arr, 0, k - 1);
    rev(arr, k, size - 1);
}

int main(){
  int arr[] = {1,2,3,4,5,6,7};
  int size = sizeof arr/ sizeof arr[0];
  rotateArrRightK(arr, size, 2);
  for(int i = 0; i < size; i++){
    printf("%d ", arr[i]);
  }
  return 0;
}
