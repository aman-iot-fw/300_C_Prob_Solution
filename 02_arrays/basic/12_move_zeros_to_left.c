#include <stdio.h>

void moveZerosLeft(int arr[], int size)
{
    int write = size - 1;

    for(int i = size - 1; i >= 0; i--)
    {
        if(arr[i] != 0)
        {
            arr[write] = arr[i];
            write--;
        }
    }

    while(write >= 0)
    {
        arr[write] = 0;
        write--;
    }
}

void printArray(int arr[], int size)
{
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int main()
{
    int arr[] = {1,2,0,4,3,0,5,0};

    int size = sizeof(arr)/sizeof(arr[0]);

    moveZerosLeft(arr, size);

    printArray(arr, size);

    return 0;
}
