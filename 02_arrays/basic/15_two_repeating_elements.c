#include <stdio.h>

void findRepeating(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if(arr[i] == arr[j])
            {
                printf("%d ", arr[i]);
                break;
            }
        }
    }
}

int main()
{
    int arr[] = {4,2,4,5,2,3,1};
    int size = sizeof(arr)/sizeof(arr[0]);

    findRepeating(arr, size);

    return 0;
}
