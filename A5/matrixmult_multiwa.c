/**
 * Description: This C program executes multiple matrix multiplications in parallel. It reads matrices for execution from command-line arguments and creates child processes for each matrix multiplication task. Each child process redirects its output to separate output and error files. The parent process waits for all child processes to complete and reports their status.
 * Author names: Abel Seno & Amirali Marsahifar
 * Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
 * Last modified date: 10/18/2023
 * Creation date: 10/7/2023
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

/**
 * This is the main function that executes multiple matrix multiplications in parallel. It reads all matrices for all executions from stdin on one line of input.
 * Input parameters: argc (the number of command-line arguments), argv (an array of strings containing the command-line arguments)
 * Returns: 0 (success) or integer greater than 0 (failure)
**/
int main(int argc, char *argv[]) {

    // Check the number of arguments
    if(argc < 3){ // Check for 2 files
        fprintf(stderr, "Error - expecting at least 2 files as input.\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    // Create a pipe for communication between parent and child processes
    int pipes[argc - 2][2]; // One pipe for each child

    // Loop through the W matrices and fork a child process for each
    for (int i = 2; i < argc; i++) {

        // Create a new process
        int pid = fork();

        // fork() was unsuccessful
        if (pid == -1) {
            fprintf(stderr, "Fork failed\n");
            return 1;
        }

        // Child process
        if (pid == 0) {

            // Redirect stdin to read from the pipe
            dup2(pipes[i - 2][0], STDIN_FILENO);

            // Close the files we don't need
            close(pipes[i - 2][0]);
            close(pipes[i - 2][1]);

            // Use execvp to replace the child process with matrixmult_parallel
            char *matrixmult_args[] = {"./matrixmult_parallel", argv[i], NULL};
            execvp("./matrixmult_parallel", matrixmult_args);

            // execvp() was unsuccessful
            fprintf(stderr, "execvp failed\n");
            return 1;

        }
    }

    // Parent process
    // Write the A matrix file name from command line to pipe
    for (int i = 0; i < argc - 2; i++) {
        write(pipes[i][1], argv[1], sizeof(argv[1]));
    }

    char line[100];

    // Read input until EOF
    while (fgets(line, sizeof(line), stdin) != NULL) {
        fflush(stdin);
        
        char *newline = strchr(line, '\n');
        if (newline) {
            *newline = '\0';
        }

        // Write the matrix to all child processes
        for (int i = 0; i < argc - 2; i++) {
            write(pipes[i][1], line, strlen(line) + 1);
        }
        
    }

    // Send null character to child to terminate loop and close
    for (int i = 0; i < argc - 2; i++) {
        char termination_signal = '\0';
        write(pipes[i][1], &termination_signal, sizeof(char));
        close(pipes[i][1]);
    }

    return 0;
}
