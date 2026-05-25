#include<stdio.h>

int arr[] = {1,2,3,4,5,6,7,8,9,0};

void findPairWithGivenSum(int arr[], int sum, int size){
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            if((arr[i] + arr[j] == sum)){
                printf("Sum matched by adding element of index %d and %d", i, j);
            }
        }
    }
    printf("Sum not found on any indexes calculating");
}

int main(){
    int size = sizeof(arr)/sizeof(arr[0]);
    findPairWithGivenSum(arr,5,size);
    return 0;
}
