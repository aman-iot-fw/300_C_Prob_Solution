#include <stdio.h>
#include <stdint.h>
uint8_t arr[10] = {0};

void mergeTwoSortedArr(uint8_t arr1[], int arr1Size, uint8_t arr2[], int arr2Size){
    uint8_t *arr1Ptr = arr1;
    uint8_t *arr2Ptr = arr2;
    uint8_t *dst = arr;
    
    while(arr1Size > 0 && arr2Size > 0){
        if(*arr1Ptr < *arr2Ptr){
            *dst++ = *arr1Ptr++;
            arr1Size--;
        }
        else{
            *dst++ = *arr2Ptr++;
            arr2Size--;
        }
    }
    
    while(arr1Size){
        *dst++ = *arr1Ptr++;
        arr1Size--;
    }
    
    while(arr2Size){
        *dst++ = *arr2Ptr++;
        arr2Size--;
    }
  
}

void printArr(uint8_t arr[], int size){
  printf("Merged Sorted Arr :");
  for(int i = 0; i < size; i++){
     printf(" %d ", arr[i]);
  }
}

int main(){
  uint8_t arr1[5] = {1,2,3,4,5};
  uint8_t arr2[5] = {6,7,8,9,10};
  
  mergeTwoSortedArr(arr1, 5, arr2, 5);
  printArr(arr, 10);

  return 0;
  
}
