/** @file rot13.c
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
	
	// Echo argv values	
	int i;
	for(i = 1; i < argc; i++){	
		printf("%s\n",argv[i]);
	}
	
	// Create buffer for input
	char inputText[256];

	// Count will be used for a fixed number of string conversions
	// Did this so we could easily test all sys calls in one function
	int count = 0;
	
	// Loop 5 times
	while(count < 5){
	
		// Get user's input
		ssize_t n = read(0, inputText, sizeof(inputText));

		// String to hold output
		char outputText[n];
		
		if(n == 0)
			return 0;
		

		// loop through each character and add or subtract 13 from it
		// store new characters in output buffer
		for(i = 0; i<n; i++){
			if((65 <= (int)inputText[i] && (int)inputText[i] <=77) ||
					(97 <= (int)inputText[i] && (int)inputText[i] <=109)){
				outputText[i] = (char)((int)inputText[i] + 13);
			}

			else if((78 <= (int)inputText[i] && (int)inputText[i] <=90) || 
					(110 <= (int)inputText[i] && (int)inputText[i] <=122)){
				outputText[i] = (char)((int)inputText[i] - 13);
			}
			else{
				outputText[i] = inputText[i];
			}
		}

		// Write the converted string
		write(1,outputText,n);	
		count++;
	}
	// Exit after five loop iterations
	exit(0);
	return 1;
}

