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
 * This is the main function to compute array multiplication in a parallel fashion using multiple processes. It reads two input matrix files, performs array multiplication in a parallel fashion using multiple processes, and prints the result.
 * Input parameters: argc (the number of command-line arguments), argv (an array of strings containing the command-line arguments)
 * Returns: 0 (success) or integer greater than 0 (failure)
**/
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
        
    //print A matrix
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
    
    //print Wi matrix
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
     
    //This array of pipes (8 PIPES)
    int pipes[ROWS][2];
    
    int index = 1;

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
    int status;
    int pid_finished;
    while ((pid_finished = wait(&status)) > -1) {
    	int row_index = pid_finished % ROWS; // Calculate index based on pid_finished
    	close(pipes[row_index][1]);// Close the write end of one of the pipe
    	
    	if (WIFEXITED(status) && WEXITSTATUS(status) == 0) { // Child process was successful
            if (read(pipes[row_index][0], result[row_index], sizeof(int) * ROWS) < 0) { // read child->parent pipe
                fprintf(stderr, "Error reading pipe %d\n", row_index);
                return 4;
            }
        } else { // Child process failed
            fprintf(stderr, "Child process %d failed\n", pid_finished);
            return 5;
        }
        close(pipes[row_index][0]); // Close the read end of one of the pipe
    }
    
    //print results and the execution time
    printf("Result of A*W = [\n");
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
    
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    printf("Runtime %f seconds\n", elapsed);
    fflush(stdout);

    return 0;
}
