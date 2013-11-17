/* ROT13 cipher test application
 *
 * Authors: Group Member 1 <email address>
 *          Group Member 2 <email address>
 * Date:    The current time & date
 */
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "bits/fileno.h"
#include <stdio.h>


int main(int argc, char* argv[]) {
	char block[256];
	char c;
	int numLetters;
	int i, out;
	char introString[40]="\nEnter characters to rotate:\n";
	printf("Started rot13\n");

	// Perform rot13 on the string the user types at runtime
	while(1) {
		// print introString to screen
		out = write(STDOUT_FILENO, introString, sizeof(introString));
		// read in the user's characters to rotate
		numLetters = read(STDIN_FILENO, block, sizeof(block));
		
		// rotate the characters
		if(numLetters == 0)
			exit(0);
		if(numLetters < 0)
			exit(1);
		for(i = 0; i < numLetters; i++) {
			c = block[i];
			if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
				block[i] = c + 13;
			else if (( c>= 'n' && c <= 'z') || (c>='N' && c <= 'Z'))
				block[i] = c - 13;
		}
		// add a new line to the end of the rotation
		block[i+1] = '\n'; 
		// increase numLetters bc of newline
		numLetters += 1;
		// write out the rotation + newline
		out = write(STDOUT_FILENO, block, numLetters * sizeof(char));
	  	
		// make sure it wrote properly
		if(out < 0)
			exit(1);	
		// if it didn't write everything, keep writing until it's all there
		while(out < numLetters)
			out+= write(STDOUT_FILENO, &block[out-1], (numLetters - out) * sizeof(char));	
	} 
	printf("Ended rot13\n");
	return 0;
}
