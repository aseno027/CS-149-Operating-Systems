Assignment 4 FA23

Description: 
In this project, we extended my program from Assignment 3 to create matrixmult_multiw_deep.c, a C program that performs parallel matrix multiplication. We created  child processes using fork and exec to execute multiplications in parallel, with results sent back to the parent process via pipes. We then summed these results to form the Rsum matrix, which served as the input for the next batch of W matrices, creating a layered, iterative calculation process. Throughout the project, we ensured the program concluded by printing the final Rsum matrix to stdout after processing all input lines.

Author names: Abel Seno & Amirali Marsahifar
Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
Last modified date: 10/31/2023
Creation date: 10/25/2023
Code:

Important: Compile the program "matrixmult_parallel.c" before compiling matrixmult_multiw.c to create "./matrixmult_parallel" which is used in matrixmult_multiw.c

Compile this program first: gcc -o matrixmult_parallel matrixmult_parallel.c -Wall -Werror

Then compile the program: gcc -o matrixmult_multiw_deep matrixmult_multiw_deep.c -Wall -Werror

Test Cases:



Input: ./matrixmult_multiw_deep A1.txt W1.txt W2.txt W3.txt



Example Output:
[
540543579 540549176 940187704 941635616 169883680 540549176 540549176 941635594 
941635616 173869600 936944 1 0 0 0 0 
0 0 4718712 1 936944 1 1876063432 1 
16777234 26 4817664 1 1876062896 1 4355932 1463943169 
1876066150 1 1920169263 1651076143 1876062248 1 1876062208 1 
-2029863744 1 1876062127 1 1876062048 1 4546264 -1659109375 
777879552 0 605364041 0 333152256 2 4325376 1 ] 