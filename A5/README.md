**Assignment 5 FA23**

* Description: This C program, matrixmult_multiwa.c, extends the functionality of Assgt3, introducing a dynamic approach to handle an arbitrary number of input matrices. It continuously reads new matrices (Anew) from stdin, multiplying each Anew with pre-existing Wi matrices in child processes. The resulting matrices are stored and dynamically reallocated in memory as needed.
* Author names: Abel Seno & Amirali Marsahifar
* Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
* Last modified date: 11/20/2023
* Creation date: 11/9/2023

**Code:**

* **Important:** Compile the program "matrixmult.c" before compiling matrixmult_multiw.c to create "./matrixmult" which is used in matrixmult_multiwa.c

* Compile this program first: gcc -o matrixmult matrixmult.c -Wall -Werror
	
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

	$ cat 4557.out
	Starting command 1: child 4557 pid of parent 4556
	test/W1.txt
	test/A1.txt
	test/A2.txt
	test/A3.txt
	test/A1.txt
	Resulting Matrix:
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
	Finished child 4557 pid of parent 4556
	Exited with exit code = 0

	$ cat 4557.err

	$ cat 4558.out
	Starting command 2: child 4558 pid of parent 4556
	test/W2.txt
	test/A1.txt
	test/A2.txt
	test/A3.txt
	test/A1.txt
	Resulting Matrix:
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
	Finished child 4558 pid of parent 4556
	Exited with exit code = 0

	$ cat 4558.err

	$ cat 4559.out
	Starting command 3: child 4559 pid of parent 4556
	test/W3.txt
	test/A1.txt
	test/A2.txt
	test/A3.txt
	test/A1.txt
	Resulting Matrix:
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
	Finished child 4559 pid of parent 4556
	Exited with exit code = 0
	
	$ cat 4559.err
	
**Average Runtime (We ran the program 3 times using the time command):** 15.091 seconds

**No Memory Leaks Using Valgrind:**

	$ valgrind --leak-check=full ./matrixmult_multiwa test/A1.txt test/W1.txt test/W2.txt test/W3.txt
	==4742== Memcheck, a memory error detector
	==4742== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
	==4742== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
	==4742== Command: ./matrixmult_multiwa test/A1.txt test/W1.txt test/W2.txt test/W3.txt
	==4742== 
	test/A2.txt
	test/A3.txt
	test/A1.txt
	==4742== 
	==4742== HEAP SUMMARY:
	==4742==     in use at exit: 0 bytes in 0 blocks
	==4742==   total heap usage: 10 allocs, 10 frees, 23,392 bytes allocated
	==4742== 
	==4742== All heap blocks were freed -- no leaks are possible
	==4742== 
	==4742== For lists of detected and suppressed errors, rerun with: -s
	==4742== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

