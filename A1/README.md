Assignment 1 FA23

* Description: This module performs matrix multiplication and addition. Given input matrices A, W, and B, it calculates R = (A * W + B) and prints the resulting matrix R. The dimensions of matrices are fixed: A is 1x3, W is 3x5, and B is 1x5.
* Author names: Abel Seno & Amirali Marsahifar
* Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
* Last modified date: 9/7/2023
* Creation date: 8/31/2023

Code:

* To compile the program: gcc -o matrixmult matrixmult.c -Wall -Werror

Test Cases:

* Test cases are located in the A1/test directory.
* To run them, use the following command format: ./matrixmult test/[TestFileNameA] test/[TestFileNameW] test/[TestFileNameB]

Expected Outputs:

Test Case 1:
Input: ./matrixmult A1.txt W1.txt B1.txt
Expected Output: Result of A*W+B = [ 111 191 391 51 11 ]

Test Case 2:
Input: ./matrixmult A2.txt W2.txt B2.txt
Expected Output: Result of A2*W2+B2 = [ 701 151 191 51 11 ]

Test Case 3:
Input: ./matrixmult A3.txt W3.txt B3.txt
Expected Output: Result of A3*W3+B3 = [ 11 19 39 55 55 ]

