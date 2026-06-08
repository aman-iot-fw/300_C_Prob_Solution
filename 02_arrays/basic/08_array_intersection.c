#include<stdio.h>
#include<stdint.h>

void intersection(int arr1[], int size1, int arr2[], int size2){
  printf("Intersection : ");
  for(int i = 0; i < size1; i++){
   for(int j = 0; j < size2; j++){
     if(arr1[i] == arr2[j]){
       printf("%d ", arr1[i]);
       break;
     }
    }
  }
}

int main(){
  int arr1[] = {1,2,4,6,7,3};  
  int size1 = sizeof arr1/ sizeof arr1[0];
    int arr2[] = {2,5,7,8,3,1,2,9,6};  
  int size2 = sizeof arr2/ sizeof arr2[0];
  intersection(arr1, size1, arr2, size2);
  return 0;
}

