#include<stdio.h>

void swap(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int partition(int *arr, int low, int high){
  int pivot = arr[high];
  int i = low - 1;

  for(int j = low; j < high; j++){
    if(arr[j] < pivot){
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i+1], &arr[high]);
  return i + 1;
  
}

void quickSort(int *arr, int low, int high){
  if(low < high){
    int pivot_idx = partition(arr, low, high);
    quickSort(arr, low, pivot_idx - 1);
    quickSort(arr, pivot_idx + 1, high);
  }
}

void printArr(int *arr, int size){
  for(int i = 0; i < size; i++){
    printf("%d ", arr[i]);
  }
}

int main(){
  int arr[] = {12,43,75,11,6,9,23,56};
  int size = sizeof arr/ sizeof arr[0];
  printf("Original Array : ");
  printArr(arr, size);

  quickSort(arr, 0, size - 1);  
  
  printf("\nSorted Array : ");
  printArr(arr, size);
  return 0;
}
