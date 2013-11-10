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
	int numLetters;
	//char letterCount[50];
	int out;
	char introString[40]="\nEnter A String:\n";
	printf("Started typo\n");

	while(1) {
		// print introString to screen
		out = write(STDOUT_FILENO, introString, sizeof(introString));
		// read in the user's characters to rotate
		numLetters = read(STDIN_FILENO, block, sizeof(block));
		
		if(numLetters == 0)
			exit(0);
		if(numLetters < 0)
			exit(1);
		// add a new line to the end of the rotation
		block[numLetters] = '!'; 
		// increase numLetters bc of newline
		numLetters += 1;
		// write out the String + newline
		out = write(STDOUT_FILENO, block, numLetters * sizeof(char));
	  	//letterCount = ;
		//write(STDOUT_FILENO, letterCount, sizeof(letterCount) * sizeof(char));	
		// make sure it wrote properly
		if(out < 0)
			exit(1);	
		// if it didn't write everything, keep writing until it's all there
		while(out < numLetters)
			out+= write(STDOUT_FILENO, &block[out-1], (numLetters - out) * sizeof(char));	
	
		sleep(100);
	} 
	//printf("Systime = %lu\n", time());
	return 0;
}
