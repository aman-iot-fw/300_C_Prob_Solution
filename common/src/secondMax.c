#include <stdio.h>
#include <stdint.h>
#include <limits.h>
int main(){
    int arr[5] = {5,5,5,5,5};
    int max =INT_MIN;
    int secondMax=INT_MIN;

    for(uint8_t i =0; i< 5;i++){
        if(arr[i] > max){
            secondMax = max;
            max = arr[i];
        }
        else if(arr[i] > secondMax && arr[i] != max){
            secondMax = arr[i];
        }
    }

    if(secondMax == INT_MIN)
    printf("No distinct second largest");
    else
    printf("%d", secondMax);
}
