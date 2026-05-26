#include<stdio.h>
#include<stdint.h>

#define SIZE 9

int arr[SIZE] = {2,4,5,2,6,2,4,4,5};

typedef struct metaData{
    int value;
    int count;
} metaData_t;

metaData_t mD[SIZE] = {0};

void removeDuplicate(int *arr, int size){

    for(int i = 0; i < size; i++){

        // Skip already processed elements
        if(mD[i].count != 0)
            continue;

        mD[i].value = arr[i];
        mD[i].count = 1;

        for(int j = i + 1; j < size; j++){

            if(arr[i] == arr[j]){

                mD[i].count++;

                // Mark duplicate as visited
                mD[j].count = -1;
            }
        }
    }
}

int main(){

    size_t size = sizeof(arr) / sizeof(arr[0]);

    removeDuplicate(arr, size);

    for(int i = 0; i < size; i++){

        if(mD[i].count > 0){

            printf("Value : %d, Count : %d\n",
                    mD[i].value,
                    mD[i].count);
        }
    }

    return 0;
}