#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>


int main(int argc, char *argv[]) {

    // Check the number of arguments
    if (argc < 3) {
        fprintf(stderr, "Usage: %s A_matrix W_matrix1 W_matrix2 ... W_matrixN\n", argv[0]);
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
            char out_filename[64];
            char err_filename[64];
            strcpy(out_filename, pid_str);
            strcpy(err_filename, pid_str);
            strcat(out_filename, ".out");
            strcat(err_filename, ".err");
            
            // Open output and error files
            int out_fd = open(out_filename, O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_fd = open(err_filename, O_RDWR | O_CREAT | O_APPEND, 0777);
        
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
    int pid;
    
    while ((pid = wait(&status)) > 0){
        // Convert pid (Integer) to a String
	char pid_str[32];
	sprintf(pid_str, "%d", pid);
		    
	// Create output and error file names using the PID
	char out_filename[64];
	char err_filename[64];
	strcpy(out_filename, pid_str);
	strcpy(err_filename, pid_str);
	strcat(out_filename, ".out");
	strcat(err_filename, ".err");
		    
	// Open output and error files
	int out_fd = open(out_filename, O_RDWR | O_CREAT | O_APPEND, 0777);
	int err_fd = open(err_filename, O_RDWR | O_CREAT | O_APPEND, 0777);
		
	// Redirect stdout and stderr to the output and error files
	dup2(out_fd, 1);
	dup2(err_fd, 2);
		    
	// Close the files we don't need
	close(out_fd);
	close(err_fd);
    
        if (WIFEXITED(status)) {
            printf("Finished child %d pid of parent %d\n", pid, getpid());
            fflush(stdout);
	    printf("Exited with exitcode = %d\n", WEXITSTATUS(status));
	    fflush(stdout);
	} else if (WIFSIGNALED(status)) {
       	    fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
       	}
    }
       
    return 0;
}
