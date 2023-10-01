#include "apue.h"
#include <stdio.h>

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid != 0) { /* parent */
        printf("Parent Process ID: %d\n", getpid());
        sleep(2);
        exit(2); /* terminate with exit status 2 */
    }

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid != 0) { /* first child */
        printf("First Child Process ID: %d\n", getpid());
        sleep(4);
        abort(); /* terminate with core dump */
    }

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid != 0) { /* second child */
        printf("Second Child Process ID: %d\n", getpid());
        execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
        exit(7); /* shouldn't get here */
    }

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid != 0) { /* third child */
        printf("Third Child Process ID: %d\n", getpid());
        sleep(8);
        exit(0); /* normal exit */
    }

    printf("Fourth Child Process ID: %d\n", getpid());
    sleep(6); /* fourth child */
    kill(getpid(), SIGKILL); /* terminate w/signal, no core dump */
    exit(6); /* shouldn't get here */
}
