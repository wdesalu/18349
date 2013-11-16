/* TYPO test application
 *
 * Authors: adesalu, kafisher, lrbloch
 * Date:    11/10/13
 */
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "bits/fileno.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	char block[256];
	int numLetters;
	unsigned long start_time;
	unsigned long end_time;
	int out;
	char introString[40]="\nEnter A String:\n";

	while(1) {
		// print introString to screen
		out = write(STDOUT_FILENO, introString, sizeof(introString));
		// time when user begins to type:
		start_time = time();
		// read in the user's characters to rotate
		numLetters = read(STDIN_FILENO, block, sizeof(block));
		// time when user is done typing:
		end_time = time();		
		if(numLetters == 0)
			exit(0);
		if(numLetters < 0)
			exit(1);
		// add a new line to the end of the string
		block[numLetters] = '\n'; 
		// increase numLetters bc of newline
		numLetters += 1;
		// write out the String + newline
		out = write(STDOUT_FILENO, block, numLetters * sizeof(char));
		
		// make sure it wrote properly
		if(out < 0)
			exit(1);	
		// if it didn't write everything, keep writing until it's all there
		while(out < numLetters)
			out+= write(STDOUT_FILENO, &block[out-1], (numLetters - out) * sizeof(char));	
		printf("%d.%ds\n", (int) (end_time - start_time)/1000, (int) (end_time - start_time) % 1000);
	} 
	return 0;
}
