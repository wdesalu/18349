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
	// Writes each character and erases it after 200ms	
	while(1){
		write(1,"|",1);
		sleep(200);
		
		write(1,"\b \b", 3);
		write(1,"/",1);
		sleep(200);

		write(1,"\b \b", 3);
		write(1,"-",1);
		sleep(200);
		
		write(1,"\b \b", 3);
		write(1,"\\",1);
		sleep(200);
		
		write(1,"\b \b", 3);
	}
	return 0;
}
