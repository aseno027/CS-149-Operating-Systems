Assignment 3 FA23

* Description: In this assignment, we developed a program named matrixmult_multiw that executes multiple matrix multiplications in parallel. This program reads a single A matrix and any number of additional W matrices as command-line arguments. Each pair of A and Wi matrices will be processed in parallel by spawning child processes that execute the matrixmult_parallel program. The results of these matrix multiplications, along with diagnostic messages, will be written to output and error files.
* Author names: Abel Seno & Amirali Marsahifar
* Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
* Last modified date: 10/11/2023
* Creation date: 10/7/2023

Code:

* To compile the program: gcc -o matrixmult_multiw matrixmult_multiw.c -Wall -Werror

Test Cases:

* Test cases are located in the A3/test directory.
* To run them, use the following command format: 
	./matrixmult_multiw test/[TestFileNameA] test/[TestFileNameW1] test/[TestFileNameW2] ... test/[TestFileNameWn]

Test Case:
Input: ./matrixmult_multiw test/A1.txt test/W1.txt test/W2.txt test/W3.txt

Example Output:

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

Average Runtime (We ran the program 3 times using the time command): 0.0423 seconds
