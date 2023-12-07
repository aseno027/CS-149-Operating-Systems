**Assignment 6 FA23**

* Description: This C program performs matrix multiplication using multi-threading. It reads a matrix from a file, receives input matrices from standard input, and calculates the result matrix by distributing the workload across multiple threads. The program utilizes pthreadsand includes synchronization using mutex to update the result matrix safely.
* Author names: Abel Seno & Amirali Marsahifar
* Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
* Last modified date: 12/6/2023
* Creation date: 12/2/2023

**Code:**

* **Important:** Compile the program "matrixmult_threaded.c" before compiling matrixmult_multiw.c to create "./matrixmult_threaded" which is used in matrixmult_multiwa.c

* Compile this program first: gcc -D_REENTRANT -pthread -o matrixmult_threaded matrixmult_threaded.c -Wall -Werror
	
* Then compile the program: gcc -o matrixmult_multiwa matrixmult_multiwa.c -Wall -Werror

**Test Cases:**

* Test cases are located in the A5/test directory.
* To run them, use the following command format: 
	./matrixmult_multiwa test/[TestFileNameA] test/[TestFileNameW1] test/[TestFileNameW2] ... test/[TestFileNameWn]

**Test Case:**

**Input:** ./matrixmult_multiwa test/A1.txt test/W1.txt test/W2.txt test/W3.txt

**Then:** There will be six new files create which are three somePID.out and three somePID.err files.

**Example Output:**

	$ ./matrixmult_multiwa test/A1.txt test/W1.txt test/W2.txt test/W3.txt
	test/A2.txt
	test/A3.txt
	test/A1.txt

	$ cat 42622.out
	Starting command 1: child 42622 pid of parent 42621
	test/W1.txt
	test/A1.txt
	test/A2.txt
	test/A3.txt
	test/A1.txt
	Result Matrix = 
	110 190 390 50 10 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	70 150 190 50 10 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	11 19 39 5 1 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	110 190 390 50 10 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	Finished child 42622 pid of parent 42621
	Exited with exit code = 0

	$ cat 42622.err

	$ cat 42623.out
	Starting command 2: child 42623 pid of parent 42621
	test/W2.txt
	test/A1.txt
	test/A2.txt
	test/A3.txt
	test/A1.txt
	Result Matrix = 
	1600 190 390 50 10 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	700 150 190 50 10 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	280 19 39 5 1 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	1600 190 390 50 10 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	Finished child 42623 pid of parent 42621
	Exited with exit code = 0

	$ cat 42623.err

	$ cat 42624.out
	Starting command 3: child 42624 pid of parent 42621
	test/W3.txt
	test/A1.txt
	test/A2.txt
	test/A3.txt
	test/A1.txt
	Result Matrix = 
	110 190 390 550 550 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	70 150 190 110 70 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	11 19 39 55 55 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	110 190 390 550 550 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	0 0 0 0 0 0 0 0 
	Finished child 42624 pid of parent 42621
	Exited with exit code = 0
	
	$ cat 42624.err
	
**Average Runtime (We ran the program 3 times using the time command):** 13.921 seconds

**No Memory Leaks Using Valgrind:**

	$ valgrind --leak-check=full ./matrixmult_multiwa test/A1.txt test/W1.txt test/W2.txt test/W3.txt
	==43433== Memcheck, a memory error detector
	==43433== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
	==43433== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
	==43433== Command: ./matrixmult_multiwa test/A1.txt test/W1.txt test/W2.txt test/W3.txt
	==43433== 
	test/A2.txt
	test/A3.txt
	test/A1.txt
	==43433== 
	==43433== HEAP SUMMARY:
	==43433==     in use at exit: 0 bytes in 0 blocks
	==43433==   total heap usage: 10 allocs, 10 frees, 23,392 bytes allocated
	==43433== 
	==43433== All heap blocks were freed -- no leaks are possible
	==43433== 
	==43433== For lists of detected and suppressed errors, rerun with: -s
	==43433== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

