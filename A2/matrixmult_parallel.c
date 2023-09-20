#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MATRIX_SIZE 8


/**
 * This function reads a matrix from a file and saves it
 * Assumption: matrices file exists in the directory
 * Input parameters: filename, numRows, numCols, matrix
 * Returns: a integer (1 == fail or 0 == success)
**/
int readMatrixFile(const char *filename, int numRows, int numCols, int matrix[numRows][numCols]){
    FILE *fp = fopen(filename,"r") ;
    if(fp == NULL){
        fprintf(stderr, "error: cannot open file %s\n", filename);
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    const char s[2] = " ";
    char *token;
    //Loop through each row in the matrix file
    for (int i = 0; i < numRows; i++) {
    	char values[80];
    	fgets(values, sizeof(values), fp);
    	token = strtok(values, s); //get string in matrix (number)
    	//Loop through each column in the matrix
        for (int j = 0; j < numCols; j++) {
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
void matrixCalculation(int matrixA[MATRIX_SIZE][MATRIX_SIZE], int matrixW[MATRIX_SIZE][MATRIX_SIZE], int resultMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
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

    int A[MATRIX_SIZE][MATRIX_SIZE] = 0;
    int W[MATRIX_SIZE][MATRIX_SIZE] = 0;
    int result[MATRIX_SIZE][MATRIX_SIZE] = 0;

    if (readMatrixFile(argv[1], MATRIX_SIZE, MATRIX_SIZE, A) == 1)
        return 1; 
    if (readMatrixFile(argv[2], MATRIX_SIZE, MATRIX_SIZE, W) == 1)
        return 1;
     
    //This array of pipes  
    int pipes[MATRIX_SIZE][MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe creation failed");
            return 1;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            return 1;
        }
        // Child process
        if (pid == 0) { 
            close(pipes[i][0]); 

            // Matrix  multipication
            matrixCalculation(A + i, W, result + i);
            write(pipes[i][1], result[i], sizeof(int) * MATRIX_SIZE);
            close(pipes[i][1]);

            exit(0);
        }
    }

    // Parent process
    for (int i = 0; i < MATRIX_SIZE; i++) {
        close(pipes[i][1]); // Close the write end of the pipe

        // The results from each child
        read(pipes[i][0], result[i], sizeof(int) * MATRIX_SIZE);
        close(pipes[i][0]);

        wait(NULL);
    }
    //print results and the execution time
    printf("Result of A*W = [\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    printf("]\n");

    return 0;
}

