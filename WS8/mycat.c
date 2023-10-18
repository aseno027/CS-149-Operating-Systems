/**
 * Description: This C program modify the mycat.c program to write to stderr the number of bytes that were read from stdin each time. 
 * Author names: Abel Seno & Amirali Marsahifar
 * Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
 * Last modified date: 10/18/2023
 * Creation date: 10/18/2023 
 **/
 
#include "apue.h"

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		// Print the number of bytes read to stderr
		fprintf(stderr, "Number of bytes read: %d\n", n);
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");
	}
	if (n < 0)
		err_sys("read error");

	exit(0);
}
