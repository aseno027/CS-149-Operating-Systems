#Assignment 3 FA23

* Description: In this assignment, we developed a program named matrixmult_multiw that executes multiple matrix multiplications in parallel. This program reads a single A matrix and any number of additional W matrices as command-line arguments. Each pair of A and Wi matrices will be processed in parallel by spawning child processes that execute the matrixmult_parallel program. The results of these matrix multiplications, along with diagnostic messages, will be written to output and error files.
* Author names: Abel Seno & Amirali Marsahifar
* Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
* Last modified date: 10/11/2023
* Creation date: 10/7/2023

**Code:**

* To compile the program: gcc -o matrixmult_multiw matrixmult_multiw.c -Wall -Werror

**Test Cases:**

* Test cases are located in the A3/test directory.
* To run them, use the following command format: 
	./matrixmult_multiw test/[TestFileNameA] test/[TestFileNameW1] test/[TestFileNameW2] ... test/[TestFileNameWn]

Test Case:
Input: ./matrixmult_multiw test/A1.txt test/W1.txt test/W2.txt test/W3.txt

**Example Output:**

	$ ./matrixmult_multiw test/A1.txt test/W1.txt test/W2.txt test/W3.txt

	$ cat 7255.out
	Starting command 1: child 7255 pid of parent 7254
	test/A1.txt = [
	10 30 40 50 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	]
	test/W1.txt = [
	1 3 4 5 1 0 0 0 
	2 4 5 0 0 0 0 0 
	1 1 5 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	]
	Result of test/A1.txt*test/W1.txt = [
	110 190 390 50 10 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	]
	Finished child 7255 pid of parent 7254
	Exited with exitcode = 0

	$ cat 7255.err

	$ cat 7256.out
	Starting command 2: child 7256 pid of parent 7254
	test/A1.txt = [
	10 30 40 50 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	]
	test/W2.txt = [
	10 3 4 5 1 0 0 0 
	20 4 5 0 0 0 0 0 
	10 1 5 0 0 0 0 0
	10 0 0 0 0 0 0 0
	20 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	]
	Result of test/A1.txt*test/W2.txt = [
	1600 190 390 50 10 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	]
	Finished child 7256 pid of parent 7254
	Exited with exitcode = 0

	$ cat 7256.err

	$ cat 7257.out
	Starting command 3: child 7257 pid of parent 7254
	test/A1.txt = [
	10 30 40 50 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	]

	test/W3.txt = [
	1 3 4 5 1 0 0 0 
	2 4 5 2 2 0 0 0 
	1 1 5 11 12 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	]
	Result of test/A1.txt*test/W3.txt = [
	110 190 390 550 550 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	]
	Finished child 7257 pid of parent 7254
	Exited with exitcode = 0

	$ cat 7257.err
	
	$ cat 2887.err
	Killed with signal 15

**Additional Information:**

To test for the last two lines of the Example Output, we intentionally introduced a sleep(100) command in the matrixmult_parallel.c program. This sleep command is used to simulate a situation where the matrix multiplication process takes a long time to complete. By doing this, we can demonstrate how to handle situations where a matrix multiplication process needs to be terminated manually.

Inside the matrixmult_parallel.c program, locate the point in your code where the matrix multiplication computation occurs. Insert the sleep(100) command at this location, instructing the program to pause execution for 100 seconds, simulating a time-consuming operation. Recompile the matrixmult_parallel.c program after making this modification.

Run the matrixmult_multiw.c program as you normally would, providing the appropriate input matrices as command-line arguments. When you observe that the matrix multiplication process initiated by matrixmult_parallel.c is taking a long time to complete, open another terminal window. In the new terminal window, use the "killall matrixmult_parallel" command. This command will terminate all running instances of the matrixmult_parallel program. If you have multiple instances running due to matrix multiplication tasks, this command will terminate all of them.

As a result of forcefully terminating the matrixmult_parallel process, you will receive a message stating "Killed with signal 15" in a specific PID.err file. Please note that the sleep(100) command was added for testing and demonstration purposes only. In practice, the matrix multiplication processes should ideally complete in a reasonable time frame, and manual termination should be unnecessary.

**Average Runtime (We ran the program 3 times using the time command):** 0.0423 seconds
