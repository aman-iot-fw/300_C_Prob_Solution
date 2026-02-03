#include <stdio.h>
#include <stdbool.h>  // For bool, true, false

// Function to check if two pointers point to elements in the same array
// Requires the base pointer and size for safe bounds checking (standard C has no way to do this without bounds info)
bool areInSameArray(int* p1, int* p2, int* base, size_t size) {
    int* end = base + size;  // One past the last element (standard array bounds)

    // Check if both pointers are within [base, end)
    return (p1 >= base && p1 < end) && (p2 >= base && p2 < end);
}

int main() {
    // Example input
    int arr[] = {1, 2, 3, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int* ptr1 = &arr[1];
    int* ptr2 = &arr[3];

    // Check if in same array
    if (areInSameArray(ptr1, ptr2, arr, size)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}