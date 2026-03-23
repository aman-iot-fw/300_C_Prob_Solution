#include<stdio.h>
#include<limits.h>

void findSecondMax(int arr[], int size, int index, int *secondMax, int *max){
  if(size == index)
    return;

  if(arr[index] > *max){
    *secondMax = *max;
    *max = arr[index];
  }
  else if(arr[index] > *secondMax && arr[index] != *max)
    *secondMax = arr[index];

  //recursive call
  findSecondMax(arr, size, index+1, secondMax, max);
}

int main(){
  int arr[] = {5,6,2,7,8,3};
  int size = sizeof(arr)/sizeof(arr[0]);

  int secondMax = INT_MIN, max = INT_MIN;

  findSecondMax(arr, size, 0, &secondMax, &max);

  if(secondMax == INT_MIN)
    printf("No Second Max Found");
  else
    printf("SecondMax Is : %d", secondMax);

  return 0;
  
}
