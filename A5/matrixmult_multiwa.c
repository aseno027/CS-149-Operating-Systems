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

    // Open all pipes
    for (int i = 0; i < argc - 2; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

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

            // Convert pid (Integer) to a String
            char pid_str[32];
            sprintf(pid_str, "%d", getpid());

            // Create output and error file names using the PID
            char out_file[64];
            char err_file[64];
            strcpy(out_file, pid_str);
            strcpy(err_file, pid_str);
            strcat(out_file, ".out");
            strcat(err_file, ".err");

            // Open output and error files
            int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

            // Redirect stdout and stderr to the output and error files
            dup2(out_fd, 1);
            dup2(err_fd, 2);

            // Close the files we don't need
            close(out_fd);
            close(err_fd);

            // The index of the weight matrix Wi in the input arguments
            int index = i - 1;

            // Print command # and pid of child/parent
            printf("Starting command %d: child %d pid of parent %d\n", index, getpid(), getppid());
            fflush(stdout);

            //edirect stdin to read from the pipe
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
    int n = strlen(argv[1]);

    for (int i = 0; i < argc - 2; i++) {
        write(pipes[i][1], &n, sizeof(int));
        write(pipes[i][1], argv[1], n);
    }

    char line[100];

    // Read input until EOF
    while (fgets(line, sizeof(line), stdin) != NULL) {
        fflush(stdin);

        line[strlen(line - 1)] = '\0';
        int numChar = strlen(line) + 1;

        // Write the matrix to all child processes
        for (int i = 0; i < argc - 2; i++) {
            write(pipes[i][1], &numChar, sizeof(int));
            write(pipes[i][1], line, strlen(line) + 1);
        }

    }

    // Send null character to child to terminate loop
    for (int i = 0; i < argc - 2; i++) {
        char termination_signal = '\0';
        write(pipes[i][1], &termination_signal, sizeof(char));
    }

    // Close the write ends of all pipes
    for (int i = 0; i < argc - 2; i++) {
        close(pipes[i][1]);
    }

    return 0;
}
