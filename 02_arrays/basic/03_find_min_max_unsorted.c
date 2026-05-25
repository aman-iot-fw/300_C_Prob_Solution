#include <stdio.h>
#include <stdint.h>
#include <limits.h>

const int arr[] = {1,3,56,123,532, 8};
int min = arr[0];
int max = arr[0];

int main(){
    int size = sizeof(arr)/ sizeof(arr[0]);
    for(int i = 0; i < size; i++){
        if(arr[i] > max){
            max = arr[i];
        }
        else if(arr[i] < min)
            min = arr[i];
    }
    
    printf("MIN : %d MAX : %d", min, max);
    return 0;
}


