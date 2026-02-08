#include <stdio.h>
#include <stdint.h>

// Function to find the duplicate number (assumes array of size n+1 with values 1 to n, exactly one duplicate)
int findDuplicate(int arr[], int size) {
    // Phase 1: Find meeting point in cycle (Floyd's Tortoise and Hare)
    int slow = 0;
    int fast = 0;
    do {
        slow = arr[slow];
        fast = arr[arr[fast]];
    } while (slow != fast);

    // Phase 2: Find the entrance to the cycle (the duplicate)
    slow = 0;
    while (slow != fast) {
        slow = arr[slow];
        fast = arr[fast];
    }

    return slow;
}

int main() {
    int arr[] = {3, 1, 3, 4, 2};
    int size = sizeof(arr) / sizeof(arr[0]);

    int duplicate = findDuplicate(arr, size);
    printf("%d\n", duplicate);

    return 0;
}
