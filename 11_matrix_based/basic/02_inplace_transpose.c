#include <stdio.h>

#define MAX_SIZE 10  // Maximum matrix size (adjust as needed)

// Function to transpose a square matrix in-place
// Returns 0 on success, -1 if not square
int matrix_transpose(int mat[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    if (rows != cols) {
        return -1;  // Error: must be square for in-place transpose
    }

    int n = rows;  // Size (square)

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {  // Only upper triangle to avoid double swaps
            // Swap mat[i][j] and mat[j][i]
            int temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }

    return 0;  // Success
}

int main() {
    // Example matrix (square, fixed size)
    int mat[MAX_SIZE][MAX_SIZE] = {{1, 2}, {3, 4}};
    int rows = 2, cols = 2;

    // Perform transpose
    int result = matrix_transpose(mat, rows, cols);

    if (result == -1) {
        printf("Error: Matrix must be square for in-place transpose.\n");
    } else {
        // Print the transposed matrix
        printf("Transposed matrix:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%d ", mat[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
