**Assignment 4 FA23**

* Description: In this assignment, This program performs matrix multiplication using matrixmult.c from Assignment 1. It reads input matrix files and computes the result in multiple steps, updating a shared result matrix as it goes. The final result is stored in "Rsum.txt," and the program's progress is logged in separate output and error files.
* Author names: Abel Seno & Amirali Marsahifar
* Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
* Last modified date: 11/1/2023
* Creation date: 10/25/2023

**Code:**

* Compile this program first: gcc -o matrixmult matrixmult.c -Wall -Werror
	
* Then compile the program: gcc -o matrixmult_multiw_deep matrixmult_multiw_deep.c -Wall -Werror

**Test Cases:**

* Test cases are located in the A4/test directory.
* To run them, use the following command format: 
	./matrixmult_multiw_deep test/[TestFileNameA] test/[TestFileNameW1] test/[TestFileNameW2] ... test/[TestFileNameWn]

**Input:**

	./matrixmult_multiw_deep test/A1.txt test/W1.txt test/W2.txt test/W3.txt <- Press Enter
	test/W4.txt test/W5.txt test/W6.txt test/W7.txt <- Press Enter
	test/W8.txt <- Press Enter
	Ctrl+D
	
**Then:** There will be files create which are somePID.out and somePID.err files. There will also be a file called "Rsum.txt" that is used in the program to save the sum as we add more inputs.

**Example Output:**
	
	$ ./matrixmult_multiw_deep test/A1.txt test/W1.txt test/W2.txt test/W3.txt
	test/W4.txt test/W5.txt test/W6.txt test/W7.txt
	test/W8.txt
	Rsum = [
	71350 54770 54770 54770 54770 54770 54770 97080 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	]
	
	$ cat 14448.out
	Starting command: child 14448 pid of parent 14447
	Paths: test/A1.txt and test/W1.txt
	Finished child 14448 pid of parent 14447
	Exited with exitcode = 0
	
	cat 14448.err

**Average Runtime (We ran the program 3 times using the time command):** 11.557 seconds

**Addtional note:** Use valgrind to detect memory leaks and no memory leaks were detected.
