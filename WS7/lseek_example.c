
/* 
 * Authors: Abel Seno and Amirali Marashifar
 * Date: 10/16/2023
 * Description: Using lseek_example.c file provided, this program reads from an input file ("start.txt") and writes
 * 		every (1+3*n)th character to an output file ("end.txt").
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void func(char arr[], int n)
{
    // Open the file for READ only.
    int f_read = open("start.txt", O_RDONLY);
    
    // Open the file for WRITE only.
    int f_write = open("end.txt", O_WRONLY | O_CREAT, 0777);
    
    int count = 0;
    
    while (read(f_read, arr, 1)) {
        // To write the 1st byte of the input file in the output file
        if (count < n) {
            // SEEK_CUR specifies that the offset provided is relative to the current file position
            lseek(f_read, n, SEEK_CUR);
            write(f_write, arr, 1);
            count = n;
        }
        // After the nth byte (now taking the alternate nth byte)
        else {
            lseek(f_read, count, SEEK_CUR);
            write(f_write, arr, 1);
        }
    }
    
    close(f_write);
    close(f_read);
}

int main() {
    char arr[100];
    int n;
    n = 2;
    // Calling the function
    func(arr, n);
    return 0;
}
