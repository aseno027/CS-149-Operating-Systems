#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define ROWS 8
#define COLS 8

/**
 * This function reads a matrix from a file and saves it
 * Assumption: matrices file exists in the directory
 * Input parameters: filename, numRows, numCols, matrix
 * Returns: a integer (1 == fail or 0 == success)
**/
int readMatrixFile(const char *filename, int matrix[ROWS][COLS]){
    FILE *fp = fopen(filename,"r") ;
    if(fp == NULL){
        fprintf(stderr, "error: cannot open file %s\n", filename);
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    const char s[2] = " ";
    char *token;
    //Loop through each row in the matrix file
    for (int i = 0; i < ROWS; i++) {
    	char values[80];
    	fgets(values, sizeof(values), fp);
    	token = strtok(values, s); //get string in matrix (number)
    	//Loop through each column in the matrix
        for (int j = 0; j < COLS; j++) {
            if (token != NULL) {
                matrix[i][j] = atoi(token); //convert string to an interger and save
                token = strtok(NULL, s);
            } else {
                matrix[i][j] = 0; // Fill with rest zeros
            }
        }
    }
    fclose(fp);
    return 0;
}


/**
 * This function performs a multiplication (dot product) of two matrices (A*W)
 * Assumption: matrixA and matriW have 8x8 dimensions
 * Input parameters: matrixA, matrixW, resultMatrix
 * Returns: void
**/
void matrixCalculation(int matrixA[ROWS][ROWS], int matrixW[ROWS][COLS], int resultMatrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < COLS; k++) {
                resultMatrix[i][j] += matrixA[i][k] * matrixW[k][j]; //A * W
            }
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error - cannot open file\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }
    struct timespec start, finish;
    double elapsed;
    
    clock_gettime(CLOCK_MONOTONIC, &start);

    int A[ROWS][COLS];
    int W[ROWS][COLS];
    int result[ROWS][COLS];

    if (readMatrixFile(argv[1], A) == 1)
        return 1; 
    if (readMatrixFile(argv[2], W) == 1)
        return 1;
     
    //This array of pipes (8 PIPES)
    int pipes[ROWS][2];

    for (int i = 0; i < ROWS; i++) {
        if (pipe(pipes[i]) == -1) {
            fprintf(stderr, "Pipe creation failed\n");
            return 1;
        }

        pid_t pid = fork();
        if (pid == -1) {
            fprintf(stderr, "Fork failed\n");
            return 2;
        }
        
        // Child process
        if (pid == 0) { 
            close(pipes[i][0]); // Close reading end of the pipe
            matrixCalculation(A, W, result); // Matrix  multipication
            if (write(pipes[i][1], result[i], sizeof(int) * ROWS) < 0) {
            	fprintf(stderr, "Error writing to pipe\n");
            	return 3;
            }
            close(pipes[i][1]); // Close write end of the pipe
            exit(0);
        }
    }
   
    // Parent process
    for (int i = 0; i < ROWS; i++) {
        close(pipes[i][1]); // Close the write end of the pipe
        // Read the results from each child
        if (read(pipes[i][0], result[i], sizeof(int) * ROWS) < 0) {
            fprintf(stderr, "Error reading pipe\n");
            return 4;
        }
        close(pipes[i][0]); // Close the read end of the pipe
        wait(NULL); // Wait for child process to complete
    }
    
    //print results and the execution time
    printf("Result of A*W = [\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
    
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    printf("Runtime %f seconds\n", elapsed);

    return 0;
}


