#include<stdio.h>

//O(n^2)
int countOccurenceSortedArr(int arr[], int size, int target){
  int count = 0;
  for(int i = 0; i < size; i++){
    if(arr[i] == target)
      count++;
  }
  return count;
}

//O(n log n)
int firstOccurrence(int arr[], int size, int target)
{
    int low = 0;
    int high = size - 1;
    int result = -1;

    while(low <= high)
    {
        int mid = low + (high - low)/2;

        if(arr[mid] == target)
        {
            result = mid;
            high = mid - 1; // search left side
        }
        else if(arr[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return result;
}

int lastOccurrence(int arr[], int size, int target)
{
    int low = 0;
    int high = size - 1;
    int result = -1;

    while(low <= high)
    {
        int mid = low + (high - low)/2;

        if(arr[mid] == target)
        {
            result = mid;
            low = mid + 1; // search right side
        }
        else if(arr[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return result;
}

int countOccurrences(int arr[], int size, int target)
{
    int first = firstOccurrence(arr, size, target);

    if(first == -1)
        return 0;

    int last = lastOccurrence(arr, size, target);

    return last - first + 1;
}

int main()
{
    int arr[] = {1,2,2,2,3};

    int size = sizeof(arr)/sizeof(arr[0]);

    printf("Count = %d\n",
           countOccurrences(arr, size, 2));

    return 0;
}
