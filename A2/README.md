Assignment 2 FA23 : OPTION 1

* Description: This module extended the matrixmult.c program from Assignment 1 to perform array multiplication in parallel using multiple processes. Each child process calculates dot products of specific rows in matrix A against matrix W, resulting in individual rows of the result matrix. The program takes two input files, A and W, performs matrix multiplication in parallel, and handles error conditions.
* Author names: Abel Seno & Amirali Marsahifar
* Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
* Last modified date: 9/22/2023
* Creation date: 9/11/2023

Code:

* To compile the program: gcc -o matrixmult_parallel matrixmult_parallel.c -Wall -Werror

Test Cases:

* Test cases are located in the A2/test directory.
* To run them, use the following command format: ./matrixmult_parallel test/[TestFileNameA] test/[TestFileNameW]

Expected Output:

Test Case:
Input: ./matrixmult_parallel test/A.txt test/W.txt

Expected Output:
Result of A*W = [
11  7 0 0 0 11 0 0 
21 13 0 0 0 21 0 0 
16 10 0 0 0 16 0 0 
16 10 0 0 0 16 0 0 
21 13 0 0 0 21 0 0 
26 16 0 0 0 26 0 0 
26 16 0 0 0 26 0 0 
16 10 0 0 0 16 0 0 
]
Runtime 0.000000 seconds

Average Runtime (We ran the program 10 times): 0.000000 seconds
