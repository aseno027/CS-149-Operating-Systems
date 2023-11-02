/**
 * Description: This program performs matrix multiplication. It reads two input matrix files, multiplies them, and sends the result to another program. The progress is logged, and matrices are read from files provided as command-line arguments.
 * Author names: Abel Seno & Amirali Marsahifar
 * Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
 * Last modified date: 11/1/2023
 * Creation date: 9/11/2023 
 **/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ROWS 8
#define COLS 8

/**
 * This function reads a matrix from a file and saves it
 * Assumption: matrices file exists in the directory
 * Input parameters: filename, matrix
 * Returns: a integer (1 == fail or 0 == success)
**/
int readMatrixFile(const char *filename, int matrix[ROWS][COLS]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open file %s\n", filename);
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    const char s[2] = " ";
    char values[80];
    int row = 0;

    // Read lines from the file and process them
    while (fgets(values, sizeof(values), fp) && row < ROWS) {
    
    	// Remove newline character from the input
        char *newline = strchr(values, '\n');
        if (newline) {
            *newline = '\0';
        }

        char *token = strtok(values, s);
        int col = 0;

        // Tokenize the line and fill the matrix row with values
        while (token != NULL && col < COLS) {
            matrix[row][col] = atoi(token);
            token = strtok(NULL, s);
            col++;
        }
        row++;
    }

    fclose(fp);
    return 0;
}

/**
 * This function performs a multiplication (dot product) of two matrices (A*W) or (Rsum*W)
 * Assumption: all matrix are 8x8
 * Input parameters: matrixA, matrixW, resultMatrix
 * Returns: void
**/
void matrixCalculation(int matrixA[ROWS][COLS], int matrixW[ROWS][COLS], int resultMatrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < COLS; k++) {
                resultMatrix[i][j] += matrixA[i][k] * matrixW[k][j]; //A * W
            }
        }
    }
}

/**
 * This is the main function for the matrix multiplication program. It reads two input matrix files, performs matrix multiplication.
 * Input parameters: argc (the number of command-line arguments), argv (an array of strings containing the command-line arguments)
 * Returns: 0 (success) or 1 (failure)
**/
int main(int argc, char *argv[]) {

    // Check for 2 files (A and W)
    if (argc != 3) {
        fprintf(stderr, "Error - expecting exactly 2 files as input.\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        fprintf(stderr, "GOT: %d\n", argc);
        return 1;
    }
    
    // Initialize matrices for A, W, and the result
    int A[ROWS][COLS] = {0};
    int W[ROWS][COLS] = {0};
    int result[ROWS][COLS] = {0};

    // Read matrix A from the first command-line argument 
    if (readMatrixFile(argv[1], A) == 1)
        return 1;

    // Read matrix W from the second command-line argument
    if (readMatrixFile(argv[2], W) == 1)
        return 1;
    
    matrixCalculation(A, W, result);
    
    // Send result matrix to parent process in the other program
    write(0, result, sizeof(int) * ROWS);
    fflush(stdin);
    
    // Print the path of the files that's being multiplied
    printf("Paths: %s and %s\n", argv[1], argv[2]);
    fflush(stdout);
    
    return 0;
}
