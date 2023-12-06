#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ROWS 8
#define COLS 8
#define NUM_THREADS ROWS * COLS

int A[ROWS][COLS];
int W[ROWS][COLS];
int result[ROWS][COLS];
pthread_mutex_t mutex;

typedef struct {
    int row;
    int col;
} Cell;

int readMatrixFile(const char *filename, int matrix[ROWS][COLS]){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open file %s\n", filename);
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    const char s[2] = " ";
    char *token;
    for (int i = 0; i < ROWS; i++) {
        char values[80];
        fgets(values, sizeof(values), fp);
        token = strtok(values, s);
        for (int j = 0; j < COLS; j++) {
            if (token != NULL) {
                matrix[i][j] = atoi(token);
                token = strtok(NULL, s);
            } else {
                matrix[i][j] = 0;
            }
        }
    }
    fclose(fp);
    return 0;
}

void *matrixCalculationThread(void *arg) {
    Cell *cell = (Cell *)arg;
    int sum = 0;
    for (int k = 0; k < COLS; k++) {
        sum += A[cell->row][k] * W[k][cell->col];
    }

    pthread_mutex_lock(&mutex);
    result[cell->row][cell->col] = sum;
    pthread_mutex_unlock(&mutex);

    free(arg);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error - cannot open file\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        return 1;
    }

    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (readMatrixFile(argv[1], A) == 1)
        return 1; 
    if (readMatrixFile(argv[2], W) == 1)
        return 1;

    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            Cell *cell = malloc(sizeof(Cell));
            cell->row = i;
            cell->col = j;
            pthread_create(&threads[i * COLS + j], NULL, matrixCalculationThread, (void *)cell);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_lock(&mutex);
    printf("Result of A*W = [\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
    pthread_mutex_unlock(&mutex);

    pthread_mutex_destroy(&mutex);

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1e9;
    printf("Runtime %f seconds\n", elapsed);

    return 0;
}
