#include <stdio.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 4; i++) { // Fork four times!
        pid_t pid = fork();
        
        if (pid < 0) { //Failed fork()
            fprintf(stderr, "Fork failed.\n");
            return 1;
        }

        if (pid == 0) { // Child process
            printf("Hello world from PID %d!\n", getpid());
            return 0;
        }
    }

    return 0;
}
