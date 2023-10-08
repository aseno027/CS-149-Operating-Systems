#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

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



//For the new function
int main(int argc, char *argv[]) {
        if (argc < 3) {
            fprintf(stderr, "At least two matrix files are required");
            exit(1);
    }

        for (int i = 2; i < argc; i++) {
        pid_t pid = fork();
        if (pid == 0) { // Child process
            char out_filename[50];
            char err_filename[50];
            sprintf(out_filename, "%d.out", getpid());
            sprintf(err_filename, "%d.err", getpid());

            int out_fd = open(out_filename, O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_fd = open(err_filename, O_RDWR | O_CREAT | O_APPEND, 0777);

            if (out_fd == -1 || err_fd == -1) {
                perror("Error opening output/error file");
                exit(1);
            }

            dup2(out_fd, STDOUT_FILENO);
            dup2(err_fd, STDERR_FILENO);

            close(out_fd);
            close(err_fd);

            fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", i-1, getpid(), getppid());

            char* args[] = {"./matrixmult", argv[1], argv[i], NULL};
            execvp(args[0], args);

            perror("execvp failed"); // This will only be printed if execvp fails
            exit(1);
        } else if (pid > 0) { // Parent process
            // Parent will continue to spawn children for other matrices
        } else {
            perror("Fork failed");
            return 1;
        }
    }

    // Parent process waits for all child processes to complete
    int status;
    pid_t pid_finished;
    while ((pid_finished = wait(&status)) > -1) {
        char out_filename[50];
        sprintf(out_filename, "%d.out", pid_finished);

        FILE* out_file = fopen(out_filename, "a");
        if (out_file) {
            fprintf(out_file, "Finished child %d pid of parent %d\n", pid_finished, getpid());
            if (WIFEXITED(status)) {
                fprintf(out_file, "Exited with exitcode = %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                fprintf(out_file, "Killed with signal %d\n", WTERMSIG(status));
            }
            fclose(out_file);
        }
    }

    return 0;

  
       
}
