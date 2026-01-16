#include <stdio.h>
#include <stdint.h>

uint8_t arr[] = {1,2,4,6,7,9};

int main(){
    size_t size = sizeof(arr)/sizeof(arr[0]);

    for(uint8_t i = 0; i < size - 1; i++){
        if(arr[i+1] - arr[i] != 1){
            printf("Missing number %d\n", arr[i]+1);
        }
    }
    
    return 0;
}