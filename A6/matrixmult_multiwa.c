/**
 * Description: This C program executes multiple matrix multiplications in parallel. It reads matrices for execution from command-line arguments and creates child processes for each matrix multiplication task. Each child process redirects its output to separate output and error files. The parent process waits for all child processes to complete and reports their status.
 * Author names: Abel Seno & Amirali Marsahifar
 * Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
 * Last modified date: 12/6/2023
 * Creation date: 11/9/2023
 **/

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
 * Input parameters: filename, matrix
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
 * This is the main function that executes multiple matrix multiplications in parallel. It reads all matrices for all executions from stdin on one line of input.
 * Input parameters: argc (the number of command-line arguments), argv (an array of strings containing the command-line arguments)
 * Returns: 0 (success) or integer greater than 0 (failure)
**/
int main(int argc, char *argv[]) {
// Check the number of arguments
    if (argc < 3) { // Check for 2 files
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

    // Save child pid
    int child_pids[argc - 2];

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

            printf("%s\n", argv[i]);  // Print the file path for matrix Wi
            fflush(stdout);

            printf("%s\n", argv[1]);  // Print the file path for matrix Ai
            fflush(stdout);

            // Redirect stdin to read from the pipe
            dup2(pipes[i - 2][0], STDIN_FILENO);

            // Close the files we don't need
            close(pipes[i - 2][0]);
            close(pipes[i - 2][1]);

            // Use execvp to replace the child process with matrixmult_parallel
            char *matrixmult_args[] = {"./matrixmult_threaded", argv[i], NULL};
            execvp("./matrixmult_threaded", matrixmult_args);

            // execvp() was unsuccessful
            fprintf(stderr, "execvp failed\n");
            return 1;
        } else { // save child pids
            child_pids[i - 2] = pid;
        }
    }

    // Parent process
    // Close the read end of all pipes
    for (int i = 0; i < argc - 2; i++) {
        close(pipes[i][0]);
    }

    // Write first A matrix from the command line to the pipe
    int A[ROWS][COLS] = {0};

    // Read matrix A
    if (readMatrixFile(argv[1], A) == 1)
        return 1;

    for (int i = 0; i < argc - 2; i++) {
        write(pipes[i][1], A, sizeof(int) * ROWS);
    }

    // Read from stdin and write matrix Ai to the pipe
    char line[100];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        fflush(stdin);

        line[strlen(line) - 1] = '\0';
        int Ai[ROWS][COLS] = {0};

        if (readMatrixFile(line, Ai) == 1)
            return 1;

        for (int i = 0; i < argc - 2; i++) {
            // Open the child out and err files for the parent:
            // Convert pid (Integer) to a String
            char pid_str[32];
            sprintf(pid_str, "%d", child_pids[i]);

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

            printf("%s\n", line);  // Print the file path for matrix Ai
            fflush(stdout);
        }

        for (int i = 0; i < argc - 2; i++) {
            write(pipes[i][1], Ai, sizeof(int) * ROWS);
        }
    }

    // Write a termination indicator to the pipe and close the pipe
    for (int i = 0; i < argc - 2; i++) {
        A[0][0] = -1; // What to look for
        write(pipes[i][1], A, sizeof(int) * ROWS);
    }

    // Close the read end of all pipes
    for (int i = 0; i < argc - 2; i++) {
        close(pipes[i][1]);
    }

    int status;
    int child_pid;

    while ((child_pid = wait(&status)) > 0) {
        // Open the child out and err files for the parent:
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
            printf("Exited with exit code = %d\n", WEXITSTATUS(status));
            fflush(stdout);
        } else if (WIFSIGNALED(status)) { // Child process was terminated by a signal
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
            return 1;
        }
    }

    return 0;
}
