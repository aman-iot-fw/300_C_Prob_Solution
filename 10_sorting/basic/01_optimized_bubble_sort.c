#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>  

int main() {
    uint8_t arr[] = {6, 5, 4, 3, 2, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%u ", arr[i]);
    }
    printf("\n");

    for (size_t pass = 0; pass < size - 1; pass++) {
        bool swapped = false;

        for (size_t i = 0; i < size - pass - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                uint8_t temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) {
            break;  // Array is already sorted → stop early
        }
    }

    printf("Sorted array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%u ", arr[i]);
    }
    printf("\n");

    return 0;
}