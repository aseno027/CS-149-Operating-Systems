/**
 * Description: This program performs matrix multiplication using child processes. It reads input matrix files and computes the result in multiple steps, updating a shared result matrix as it goes. The final result is stored in "Rsum.txt," and the program's progress is logged in separate output and error files.
 * Author names: Abel Seno & Amirali Marsahifar
 * Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
 * Last modified date: 11/1/2023
 * Creation date: 10/25/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define ROWS 8
#define COLS 8

/**
 * This function performs matrix addition for two matrices
 * Input parameters: rSum, Bi
 * Returns: void
**/
void addMatrix(int rSum[ROWS][COLS], int Bi[ROWS][COLS]) {
    // This function performs matrix addition
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            rSum[i][j] = rSum[i][j] + Bi[i][j];
        }
    }
}

/**
 * This function does matrix multiplication in parallel using child processes. It reads input matrix files and computes the result in multiple steps, updating a shared result matrix as it goes
 * Input parameters: argc (the number of command-line arguments), argv (an array of strings containing the command-line arguments)
 * Returns: 0 (success) or1 (failure)
**/
int main(int argc, char *argv[]) {
    // Check the number of arguments
    if (argc < 3) {
        fprintf(stderr, "Error - expecting at least 2 files as input.\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    // Create a pipe for communication between parent and child processes
    int fd1[2];
    int rSum[ROWS][COLS] = {0};
    int Bi[ROWS][COLS] = {0};

    // Creating pipe was unsuccessful
    if (pipe(fd1) == -1) {
        fprintf(stderr, "Pipe creation failed\n");
        return 1;
    }

    int saved_stdout = dup(1); // Save to print Rsum to console at the end

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
            // Redirect standard input to the write end of the pipe
            dup2(fd1[1], 0);
            close(fd1[0]);
            close(fd1[1]);

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

            // Print command # and pid of child/parent
            printf("Starting command: child %d pid of parent %d\n", getpid(), getppid());
            fflush(stdout);

            // Use execvp to replace the child process with matrixmult
            char *matrixmult_args[] = {"./matrixmult", argv[1], argv[i], NULL};
            execvp("./matrixmult", matrixmult_args);

            // execvp() was unsuccessful
            fprintf(stderr, "execvp failed\n");
            return 1;
        }
    }

    // Parent process
    int status;
    int child_pid;

    // Close writing end of the pipe
    close(fd1[1]);

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

            // Read the result from the pipe and update the sum
            read(fd1[0], Bi, sizeof(int) * ROWS);
            addMatrix(rSum, Bi);
        } else if (WIFSIGNALED(status)) { // Child process was terminated by a signal
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
            return 1;
        }
    }
    close(fd1[1]);

    // Update Rsum.txt with the calculated result
    FILE *rFile = fopen("Rsum.txt", "w");
    if (rFile == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // Write the result matrix to the file
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fprintf(rFile, "%d", rSum[i][j]);
            if (j < COLS - 1) {
                fprintf(rFile, " ");
                fflush(rFile);
            }
        }
        fprintf(rFile, "\n");
        fflush(rFile);
    }
    fclose(rFile);

    // Process file names from subsequent iterations using fgets
    char line[1024];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        fflush(stdin);
        // Input empty line
        
        // Remove newline character from the input
        char* newline = strchr(line, '\n');
        if (newline) {
            *newline = '\0';
        }
        
        // Skip processing if the line is empty
        if (strlen(line) == 0) {
            continue;
        }

        // Parse the line and extract W filenames
        char *token = strtok(line, " ");
        int fd2[2];

        // Creating pipe was unsuccessful
        if (pipe(fd2) == -1) {
            fprintf(stderr, "Pipe creation failed\n");
            return 1;
        }

        // Zero out rSum array
        memset(rSum, 0, sizeof(rSum[0][0]) * ROWS * COLS);
        while (token != NULL) {
            // Create a new process
            int pid = fork();
            if (pid == -1) {
                fprintf(stderr, "Fork failed\n");
                return 1;
            }
            if (pid == 0) {
                // Child process
                dup2(fd2[1], 0);
                close(fd2[0]);
                close(fd2[1]);

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

                // Print command # and pid of child/parent
                printf("Starting command: child %d pid of parent %d\n", getpid(), getppid());
                fflush(stdout);

                // Use execvp to replace the child process with matrixmult
                char *matrixmult_args[] = {"./matrixmult", "Rsum.txt", token, NULL};
                execvp("./matrixmult", matrixmult_args);

                // execvp() was unsuccessful
                fprintf(stderr, "execvp failed\n");
                return 1;
            }
            token = strtok(NULL, " ");
        }

        // Parent process
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

                read(fd2[0], Bi, sizeof(int) * ROWS);
                addMatrix(rSum, Bi);
            } else if (WIFSIGNALED(status)) { // Child process was terminated by a signal
                fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
                return 1;
            }
        }
        close(fd2[1]);

        // Update the value of Rsum.txt
        FILE *rFile = fopen("Rsum.txt", "w");
        if (rFile == NULL) {
            perror("Failed to open file");
            return 1;
        }
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                fprintf(rFile, "%d", rSum[i][j]);
                if (j < COLS - 1) {
                    fprintf(rFile, " ");
                    fflush(rFile);
                }
            }
            fprintf(rFile, "\n");
            fflush(rFile);
        }
        fclose(rFile);
        fflush(stdin);
    }

    // Restore stdout
    dup2(saved_stdout, 1);
    close(saved_stdout);

    // Print Rsum to console
    printf("Rsum = [\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", rSum[i][j]);
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }
    printf("]\n");
    fflush(stdout);

    return 0;
}
