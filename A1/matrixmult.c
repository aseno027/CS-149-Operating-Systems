#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
 * This function performs a multiplication (dot product) of two matrices (A*W) and add
 * Assumption: matrix A have size of 1x3 and matrix W have a size of 3x5 and the matrices R and B are of dimension 1x5
 * Input parameters: matrixA, matrixW, matrixB, resultMatrix
 * Returns: void
**/
void matrixCalculation(int matrixA[1][3], int matrixW[3][5], int matrixB[1][5], int resultMatrix[1][5]) {
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 5; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                resultMatrix[i][j] += matrixA[i][k] * matrixW[k][j]; //A * W
            }
            resultMatrix[i][j] += matrixB[i][j]; //(A * W) + B
        }
    }
}

/**
 * This is the main function for the matrix multiplication program. It reads three input matrix files, performs matrix multiplication and addition, and prints the result.
 * Input parameters: argc (the number of command-line arguments), argv (an array of strings containing the command-line arguments)
 * Returns: 0 (success) or 1 (failure)
**/
int main(int argc, char *argv[]) {

    if(argc != 4){ //Check for 3 files
        fprintf(stderr, "Error - expecting exactly 3 files as input.\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    int A[1][3]; //A is 1x3
    int W[3][5]; //W is 3x5
    int B[1][5]; //B is 1x5
    int R[1][5]; //R is of dimension 1x5
    
    if(readMatrixFile(argv[1], 1, 3, A) == 1)//Read matrix A
    	return 1; //file not found
    if(readMatrixFile(argv[2], 3, 5, W) == 1)//Read matrix W
    	return 1; //file not found
    if(readMatrixFile(argv[3], 1, 5, B) == 1)//Read matrix B
    	return 1; //file not found
    
    matrixCalculation(A, W, B, R);
    
    //prints result
    printf("Result (%s * %s) + %s = [ ", argv[1], argv[2], argv[3]);
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", R[i][j]);
        }
    }
    printf("]\n");
    return 0;
}

