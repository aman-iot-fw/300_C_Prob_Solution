#include<stdio.h>
#include<stdint.h>

void segregateOddEven(int arr[], int size){
    int *left = arr;
    int *right = arr + size - 1;
    
    while(left < right){
        while(left < right && (*left % 2 == 0))
            left++;
        while(left < right && (*right % 2 != 0))
            right--;
            
        if(left < right){
            int tmp = *left;
            *left = *right;
            *right = tmp;
            
            left++;
            right--;
        }
    }
}

void printArr(int arr[], int size){
    printf("\n Array :");
    for(int i = 0; i < size; i++){
        printf(" %d", arr[i]);
    }
}


int main(){
    int arr[] = {1,4,6,33,99,3,12,10};
    int size = sizeof(arr) / sizeof(arr[0]);
    printArr(arr, size);
    segregateOddEven(arr, size);
    printArr(arr, size);
    return 0;
}

