#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define ROWS 8
#define COLS 8
#define MAX_FILES 100

void initializeMatrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = 0;
        }
    }
}

void printMatrix(int matrix[ROWS][COLS]) {
    printf("[\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}

void sumMatrices(int matrixA[ROWS][COLS], int matrixB[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrixA[i][j] += matrixB[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    int Rsum[ROWS][COLS];
    initializeMatrix(Rsum);

    char *A_file = argv[1];
    char *W_files[MAX_FILES];
    int num_W_files = argc - 2;
    for (int i = 0; i < num_W_files; i++) {
        W_files[i] = argv[i + 2];
    }

    while (1) {
        // Create child processes for each W file
        for (int i = 0; i < num_W_files; i++) {
            int pipefd[2];
            if (pipe(pipefd) == -1) {
                perror("pipe");
                return 1;
            }

            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                return 1;
            } else if (pid == 0) {
                // Child process
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);

                // Construct command line arguments for exec
                char *args[] = {"matrixmult_parallel",  A_file, W_files[i], NULL};
                if (execvp("./matrixmult_parallel", args) == -1) {
                    perror("execvp");
                    exit(1);
                }
            } else {
                // Parent process
                close(pipefd[1]);
                int result[ROWS][COLS];
                read(pipefd[0], result, sizeof(result));
                close(pipefd[0]);

                sumMatrices(Rsum, result);

                int status;
                wait(&status);
                if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                    fprintf(stderr, "Child process exited with error\n");
                }
            }
        }

        
        char line[1024];
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        char *token = strtok(line, " \n");
        num_W_files = 0;
        while (token != NULL && num_W_files < MAX_FILES) {
            W_files[num_W_files++] = strdup(token);
            token = strtok(NULL, " \n");
        }

        A_file = "Rsum";
    }

    printMatrix(Rsum);

    return EXIT_SUCCESS;
}
