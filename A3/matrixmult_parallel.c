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
 * Input parameters: filename, numRows, numCols, matrix
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
 * This function performs a multiplication (dot product) of a row in matrix A to matrix W
 * Assumption: matrixA a row in A and matriW have 8x8 dimensions
 * Input parameters: matrixA, matrixW, resultRow
 * Returns: void
**/
void matrixCalculation(int matrixA[COLS], int matrixW[ROWS][COLS], int resultRow[COLS]) {
    for (int i = 0; i < COLS; i++) {
        resultRow[i] = 0;
        for (int j = 0; j < COLS; j++) {
            resultRow[i] += matrixA[j] * matrixW[j][i];
        }
    }
}

/**
 * This is the main function to compute array multiplication in a parallel fashion using multiple processes. It reads two input matrix files, performs array multiplication in a parallel fashion using multiple processes, and prints the result.
 * Input parameters: argc (the number of command-line arguments), argv (an array of strings containing the command-line arguments)
 * Returns: 0 (success) or integer greater than 0 (failure)
**/
int main(int argc, char *argv[]) {

    // Check for 2 files (A and W)
    if (argc != 3) {
        fprintf(stderr, "Error - expecting exactly 2 files as input.\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }
	
    // sleep(100); // Used for testting only
    
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

    // Create a pipe for communication between parent and child processes
    int fd[2];

    // Creating pipe was unsuccessful
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe creation failed\n");
        return 1;
    }

    // Fork child processes for matrix calculations
    for (int i = 0; i < ROWS; i++) {

        int pid = fork();

        // fork() was unsuccessful
        if (pid == -1) {
            fprintf(stderr, "Fork failed\n");
            return 1;
        }

        // Child process: Perform matrix calculation and write results to the pipe
        if (pid == 0) {

            // Close reading end of pipe
            close(fd[0]);

            // Create and save dot product
            int resultRow[COLS] = {0};
            matrixCalculation(A[i], W, resultRow);

            // Write index value to pipe for parent
            if (write(fd[1], &i, sizeof(int)) < 0) {
                fprintf(stderr, "Error writing to pipe\n");
                exit(1); // Exit with error status in child process
            }

            // Write resultRow to pipe after computing
            if (write(fd[1], resultRow, sizeof(int) * COLS) < 0) {
                fprintf(stderr, "Error writing to pipe\n");
                exit(1); // Exit with error status in child process
            }

            // Close writing end of pipe
            close(fd[1]);
            exit(0);
        }
    }

    // Parent process
    // Close writing end of pipe
    close(fd[1]);

    // Initialized status and pid_finished for parent process to use
    int status;
    int pid_finished;

    // Wait for child processes to complete
    while ((pid_finished = wait(&status)) > 0) {

        // Child process was successful
        if (WIFEXITED(status)) {

            // Read child process index first
            int index;
            if (read(fd[0], &index, sizeof(int)) < 0) {
                fprintf(stderr, "Error reading pipe\n");
                return 1;
            }

            // Read child process resultRow array and save it
            int resultRow[COLS] = {0};
            if (read(fd[0], resultRow, sizeof(int) * COLS) < 0) {
                fprintf(stderr, "Error reading pipe\n");
                return 1;
            }

            // Save it to result matrix using index and resultRow that was read from child
            for (int j = 0; j < COLS; j++) {
                result[index][j] = resultRow[j];
            }

        } else if (WIFSIGNALED(status)) {

            fprintf(stderr, "Child %d terminated abnormally with signal number: %d\n", pid_finished, WTERMSIG(status));

        }
    }

    // Close reading end of pipe
    close(fd[0]);

    //PRINT ALL THE MATRIX TO STDOUT:
    
    // Print matrix A
    printf("%s = [\n", argv[1]);
    fflush(stdout);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", A[i][j]);
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }
    printf("]\n");
    fflush(stdout);

    // Print matrix W
    printf("%s = [\n", argv[2]);
    fflush(stdout);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", W[i][j]);
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }
    printf("]\n");
    fflush(stdout);

    // Print the result matrix
    printf("Result of %s*%s = [\n", argv[1], argv[2]);
    fflush(stdout);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", result[i][j]);
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }
    printf("]\n");
    fflush(stdout);

    return 0;
}
