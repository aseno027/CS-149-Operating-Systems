/**
 * Description: This C program performs matrix multiplication. It reads matrix W from the command-line argument and continuously reads matrices A from standard input. It creates child processes to perform matrix multiplication, and the resulting matrices are printed to standard output. The program stops when a termination indicator is received.
 * Author names: Abel Seno & Amirali Marsahifar
 * Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
 * Last modified date: 11/20/2023
 * Creation date: 11/9/2023
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
        // Print an error message if the file cannot be opened
        fprintf(stderr, "error: cannot open file %s\n", filename);
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    const char s[2] = " ";
    char values[80];
    int row = 0;

    // Read lines from the file and process them
    while (fgets(values, sizeof(values), fp) && row < ROWS) {

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
 * This function performs a multiplication (dot product) of two matrices (A*W).
 * It dynamically allocates memory for the result matrix using malloc or realloc based on whether the result matrix already exists.
 * Input parameters: matrixA, matrixW, resultMatrix, resultRows.
 * Returns: void
**/
void matrixCalculation(int matrixA[ROWS][COLS], int matrixW[ROWS][COLS], int ***resultMatrix, int *resultRows) {
    if (*resultMatrix == NULL) {
        // Initialize the result matrix if it doesn't exist
        *resultRows = ROWS;
        *resultMatrix = (int **)malloc(*resultRows * sizeof(int *));
        for (int i = 0; i < *resultRows; i++) {
            (*resultMatrix)[i] = (int *)malloc(COLS * sizeof(int));
        }
    } else {
        // Resize the result matrix using realloc
        *resultRows += ROWS;
        *resultMatrix = (int **)realloc(*resultMatrix, *resultRows * sizeof(int *));
        for (int i = *resultRows - ROWS; i < *resultRows; i++) {
            (*resultMatrix)[i] = (int *)malloc(COLS * sizeof(int));
        }
    }

    for (int i = *resultRows - ROWS; i < *resultRows; i++) {
        for (int j = 0; j < COLS; j++) {
            (*resultMatrix)[i][j] = 0;
            for (int k = 0; k < COLS; k++) {
                (*resultMatrix)[i][j] += matrixA[i - (*resultRows - ROWS)][k] * matrixW[k][j]; // A * W
            }
        }
    }
}

/**
 * This is the main function that reads matrix W from the command-line argument and continuously reads matrices A from standard input.
 * It creates child processes to perform matrix multiplication, and the resulting matrices are allocated to result.
 * The program stops when a termination indicator is received.
 * Input parameters: argc (the number of command-line arguments), argv (an array of strings containing the command-line arguments)
 * Returns: 0 (success) or 1 (failure)
**/
int main(int argc, char *argv[]) {

    // Check for 1 file (W)
    if (argc != 2) {
        // Print an error message if the number of files is not as expected
        fprintf(stderr, "Error - expecting exactly 2 files as input.\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        fprintf(stderr, "GOT: %d\n", argc);
        return 1;
    }

    // Initialize matrices for A, W, and the result
    int A[ROWS][COLS] = {0};
    int W[ROWS][COLS] = {0};
    int **result = NULL;
    int resultRows = 0;

    // Read matrix W from the second command-line argument
    if (readMatrixFile(argv[1], W) == 1)
        return 1;

    while (read(STDIN_FILENO, A, sizeof(int) * ROWS)) {
        if (A[0][0] == -1){
            break;
        }
        matrixCalculation(A, W, &result, &resultRows);
    }

    // Print the resulting matrix
    printf("Resulting Matrix:\n");
    fflush(stdout);
    for (int i = 0; i < resultRows; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", result[i][j]);
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }

    // Free allocated memory
    for (int i = 0; i < resultRows; ++i) {
        free(result[i]);
    }
    free(result);

    return 0;
}
