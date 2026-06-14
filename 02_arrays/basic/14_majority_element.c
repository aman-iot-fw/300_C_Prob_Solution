#include <stdio.h>

int majorityElement(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        int count = 0;

        for(int j = 0; j < size; j++)
        {
            if(arr[i] == arr[j])
                count++;
        }

        if(count > size / 2)
            return arr[i];
    }

    return -1;
}

int main()
{
    int arr[] = {3,3,4,2,4,4,2,4,4};

    int size = sizeof(arr)/sizeof(arr[0]);

    printf("Majority Element = %d\n",
           majorityElement(arr, size));

    return 0;
}
