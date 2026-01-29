#include <stdio.h>

#define MAX_SIZE 10

// Function to multiply matrices A and B, store result in C
// Returns 0 on success, -1 if dimensions incompatible
int matrix_multiply(int A[MAX_SIZE][MAX_SIZE], int rowsA, int colsA,
                    int B[MAX_SIZE][MAX_SIZE], int rowsB, int colsB,
                    int C[MAX_SIZE][MAX_SIZE]) {
    if (colsA != rowsB) {
        return -1;  // Error: incompatible dimensions
    }

    // Perform multiplication
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            C[i][j] = 0;  // Initialize element
            for (int k = 0; k < colsA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return 0;  // Success
}

int main() {
    int A[MAX_SIZE][MAX_SIZE] = {{1, 2}, {3, 4}};
    int rowsA = 2, colsA = 2;

    int B[MAX_SIZE][MAX_SIZE] = {{2, 0}, {1, 3}};
    int rowsB = 2, colsB = 2;

    int C[MAX_SIZE][MAX_SIZE];  // Result matrix

    // Perform multiplication
    int result = matrix_multiply(A, rowsA, colsA, B, rowsB, colsB, C);

    if (result == -1) {
        printf("Error: Matrices cannot be multiplied (incompatible dimensions).\n");
    } else {
        // Print the result
        printf("Result matrix:\n");
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsB; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}