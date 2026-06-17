#include <stdio.h>

void findOverlap(int *arr1, int size1,
                 int *arr2, int size2)
{
    int *p1 = arr1;
    int *p2 = arr2;

    while(p1 < arr1 + size1 &&
          p2 < arr2 + size2)
    {
        if(*p1 < *p2)
        {
            p1++;
        }
        else if(*p1 > *p2)
        {
            p2++;
        }
        else
        {
            printf("%d ", *p1);

            p1++;
            p2++;
        }
    }
}

int main()
{
    int arr1[] = {1,2,3,4,5,6};
    int arr2[] = {5,6,7,8};

    int size1 = sizeof(arr1)/sizeof(arr1[0]);
    int size2 = sizeof(arr2)/sizeof(arr2[0]);

    printf("Overlapping Elements: ");

    findOverlap(arr1, size1, arr2, size2);

    return 0;
}
