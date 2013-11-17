/** @file typo.c
 *
 * @Authors: Sara Roy <slroy@andrew.cmu.edu>
 *          Samantha Klonaris <sklonari@andrew.cmu.edu>
 *  	    Derek Miller <damiller@andrew.cmu.edu>
 * @Date: 11/4/20 
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv){
	// Never ends
	while(1){
		// Print prompt	
		printf("Enter string:\n");
		
		// Create a buffer of fixed size		
		char buf[1024];

		// Get start time
		long start_time = time();

		// Read user's input
		size_t len = read(0, buf, 1024);
		
		// Get the end time
		long end_time = time();
		
		// Echo the string
		write(1,buf,len);

		// Calculate the time difference and display in seconds.
		printf("time: %d",(int)(end_time-start_time)/1000);
		printf(".%d\n",(int)(end_time-start_time)%1000);
	}
	// Never will get here
	return 0;
}
