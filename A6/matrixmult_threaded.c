/**
 * Description: This C program performs matrix multiplication. It reads matrix W from the command-line argument and continuously reads matrices A from standard input. It creates threads to perform matrix multiplication, and the resulting matrices are allocated to result. The program stops when a termination indicator is received.
 * Author names: Abel Seno & Amirali Marsahifar
 * Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
 * Last modified date: 12/6/2023
 * Creation date: 12/2/2023
 **/

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 8
#define COLS 8
#define NUM_THREADS ROWS * COLS

int A[ROWS][COLS];
int W[ROWS][COLS];
int** result; // Dynamic 2D array for the result matrix
int resultRows; // Used when we realloc

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Structure to represent a cell in the matrices
typedef struct {
    int row; // Row index of the cell
    int col; // Column index of the cell
    int result_row; // Row index of the cell when we realloc
} Cell;

/**
 * This function reads a matrix from a file and saves it
 * Assumption: matrices file exists in the directory
 * Input parameters: filename, matrix
 * Returns: an integer (1 == fail or 0 == success)
**/
int readMatrixFile(const char *filename, int matrix[ROWS][COLS]) {
    // Open the file for reading
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

    // Close the file
    fclose(fp);
    return 0;
}

/**
 * This function represents the computation performed by each thread
 * Input parameters: a Cell struct containing the row and column of the cell
**/
void *matrixCalculationThread(void *arg) {
    Cell *cell = (Cell *)arg;
    int sum = 0;

    // Perform matrix multiplication for the given cell
    for (int k = 0; k < COLS; k++) {
        sum += A[cell->row][k] * W[k][cell->col];
    }

    // Lock the mutex before updating the result matrix
    pthread_mutex_lock(&mutex);
    result[cell->result_row][cell->col] = sum; // Critical section
    pthread_mutex_unlock(&mutex);

    // Free the dynamically allocated memory for the Cell struct
    free(arg);
    pthread_exit(NULL);
}


/**
 * This is the main function that reads matrix W from the command-line argument and continuously reads matrices A from standard input.
 * It creates threads to perform matrix multiplication, and the resulting matrices are allocated to result.
 * The program stops when a termination indicator is received.
 * Input parameters: argc (the number of command-line arguments), argv (an array of strings containing the command-line arguments)
 * Returns: 0 (success) or 1 (failure)
**/
int main(int argc, char *argv[]) {
    // Check for the correct number of command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Error - cannot open file\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    // Read the matrix W from the file specified in the command-line arguments
    if (readMatrixFile(argv[1], W) == 1)
        return 1;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);


    // Read matrices from standard input until an end signal is received
    while (read(STDIN_FILENO, A, sizeof(int) * ROWS)) {
        // Check for the end signal
        if (A[0][0] == -1) {
            break;
        }

        if (result == NULL){
            // Allocate memory for the result matrix dynamically
            resultRows = ROWS;
            result = (int **)malloc(ROWS * sizeof(int *));
            for (int i = 0; i < ROWS; i++) {
                result[i] = (int *) malloc(COLS * sizeof(int));
            }
        }else{
            // Resize the result matrix using realloc
            resultRows += ROWS;
            result = (int **)realloc(result, resultRows * sizeof(int *));
            for (int i = resultRows - ROWS; i < resultRows; i++) {
                result[i] = (int *)malloc(COLS * sizeof(int));
            }
        }

        pthread_t threads[NUM_THREADS];

        // Create threads for matrix multiplication
        int count = 0;
        for (int i = resultRows - ROWS; i < resultRows; i++) {
            for (int j = 0; j < COLS; j++) {
                Cell *cell = malloc(sizeof(Cell));
               	cell->row = count;
                cell->col = j;
                cell->result_row = i;
                pthread_create(&threads[count * COLS + j], NULL, matrixCalculationThread, (void *) cell);
            }
            count++;
        }
        count = 0;

        // Wait for all threads to finish
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }

    }

    // Lock the mutex before printing the result matrix
    pthread_mutex_lock(&mutex);
    printf("Result Matrix = \n");
    for (int i = 0; i <  resultRows; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    pthread_mutex_unlock(&mutex);

    // Free allocated memory
    for (int i = 0; i < resultRows; ++i) {
        free(result[i]);
    }
    free(result);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
