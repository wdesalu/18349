/* EQUAL- Test if time calls with no time between them or 
 * small amounts of time between them are equal.
 * Authors: Laura Bloch, Wale Desalu, Kylie Fisher
 *          
 * Date:   11/10/2013
 */
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "bits/fileno.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	long time1, time2;

	/* Test if consecutive time calls are equal */
	time1 = time();
	time2 = time();
	if (time1 == time2)
		printf("Consecutive time calls are equal. Success.\n");
	else
		printf("Consecutive time calls are not equal. Failure.\n");
	
	/* Test if time calls are different with 1 ms sleep */
	time1 = time();
	sleep(1);
	time2 = time();
	if (time1 != time2)
		printf("Time calls with small interval are not equal. Success\n");
	else
		printf("Time calls with small interval are equal. Failure.\n");

	return 0;
}
