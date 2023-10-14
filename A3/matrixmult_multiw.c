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

            // Use execvp to replace the child process with matrixmult_parallel
            char *matrixmult_args[] = {"./matrixmult_parallel", argv[1], argv[i], NULL};
            execvp("./matrixmult_parallel", matrixmult_args);

            // execvp() was unsuccessful
            fprintf(stderr, "execvp failed\n");
            return 1;

        }
    }

    // Parent process
    int status;
    int child_pid;
    while ((child_pid = wait(&status)) > 0) {
    
    	// Open the child out and err files for parent:
        // Convert pid (Integer) to a String
        char pid_str[32];
        sprintf(pid_str, "%d", child_pid);

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
        
        // Check if the child process terminated normally
        if (WIFEXITED(status)) {
            printf("Finished child %d pid of parent %d\n", child_pid, getpid());
            fflush(stdout);
            printf("Exited with exitcode = %d\n", WEXITSTATUS(status));
            fflush(stdout);
        } else if (WIFSIGNALED(status)) { // Child process was terminated by a signal
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
