#include <stdio.h>

void reverse(int *start, int *end)
{
    while(start < end)
    {
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

void rotateRight(int *arr, int size, int k)
{
    k = k % size;

    // Reverse whole array
    reverse(arr, arr + size - 1);

    // Reverse first k elements
    reverse(arr, arr + k - 1);

    // Reverse remaining elements
    reverse(arr + k, arr + size - 1);
}

void printArray(int *arr, int size)
{
    while(size--)
    {
        printf("%d ", *arr++);
    }
    printf("\n");
}

int main()
{
    int arr[] = {1,2,3,4,5};

    int size = sizeof(arr)/sizeof(arr[0]);

    int k = 2;

    rotateRight(arr, size, k);

    printArray(arr, size);

    return 0;
}
