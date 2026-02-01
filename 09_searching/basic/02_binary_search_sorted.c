#include <stdio.h>

// Function to perform binary search on a sorted array
// Returns the index of the target if found, otherwise -1
int binary_search(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow

        if (arr[mid] == target) {
            return mid;  // Found the target
        } else if (arr[mid] < target) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1;  // Search left half
        }
    }

    return -1;  // Target not found
}

int main() {
    // Example input (must be sorted ascending)
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 4;

    // Perform search
    int index = binary_search(arr, size, target);

    // Output the result
    if (index != -1) {
        printf("Target %d found at index: %d\n", target, index);
    } else {
        printf("Target %d not found in the array.\n", target);
    }

    return 0;
}