#include <stdio.h>

#define MATRIX_SIZE 4

void multiply_matrices(int A[MATRIX_SIZE][MATRIX_SIZE], int B[MATRIX_SIZE][MATRIX_SIZE], int C[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void initialize_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int value) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = value;
        }
    }
}

int main() {
    int A[MATRIX_SIZE][MATRIX_SIZE];
    int B[MATRIX_SIZE][MATRIX_SIZE];
    int C[MATRIX_SIZE][MATRIX_SIZE];

    // Initialize matrices
    initialize_matrix(A, 1);
    initialize_matrix(B, 2);
    
    // Multiply matrices
    multiply_matrices(A, B, C);

    // Print result
    printf("[\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    printf("]\n");

    return 0;
}
