#include<stdio.h>

int searchInex(int arr[], int size, int target ){
    for(int i =0; i < size; i++){
        if(arr[i] == target){
            return i;
        }
    }
    return -1;

}

int main(){
    int arr[] = {2,4,6,3,8,9};
    size_t size = sizeof(arr)/sizeof(arr[0]);
    int target = 9;

    int index = searchInex(arr, size, target);

    if(index != -1){
        printf("Index of the target number in array: %d\n", index);
    }
    else{
        printf("Target not found in the given array");
    }

    return 0;
}
