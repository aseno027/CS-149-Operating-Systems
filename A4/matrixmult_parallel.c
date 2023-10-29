/**
 * Description: This C program performs matrix multiplication in a parallel fashion using multiple processes. It reads two input matrix files, performs array multiplication, and prints the result. The program utilizes child processes for matrix calculations and a pipe for communication between the parent and child processes.
 * Author names: Abel Seno & Amirali Marsahifar
 * Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
 * Last modified date: 10/18/2023
 * Creation date: 10/7/2023 
 * Modified 10/29/2023
 **/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 8
#define COLS 8


/**
 * This function reads a matrix from a file and saves it
 * Assumption: matrices file exists in the directory
 * Input parameters: filename, numRows, numCols, matrix
 * Returns: a integer (1 == fail or 0 == success)
**/
int readMatrix(const char *filename, int matrix[ROWS][COLS]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (fscanf(fp, "%d", &matrix[i][j]) != 1) {
                matrix[i][j] = 0;
            }
        }
    }

    fclose(fp);
    return 0;
}
/**
 * This function performs a multiplication (dot product) of a row in matrix A to matrix W
 * Assumption: matrixA a row in A and matriW have 8x8 dimensions
 * Input parameters: matrixA, matrixW, resultRow
 * Returns: void
**/
void matrixMultiplication(const int A[ROWS][COLS], const int W[ROWS][COLS], int R[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            R[i][j] = 0;
            for (int k = 0; k < COLS; k++) {
                R[i][j] += A[i][k] * W[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    int A[ROWS][COLS], W[ROWS][COLS], R[ROWS][COLS];

    if (readMatrix(argv[1], A)) {
        return 1;
    }

    if (readMatrix(argv[2], W)) {
        return 1;
    }

    matrixMultiplication(A, W, R);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }

    return 1;
}
