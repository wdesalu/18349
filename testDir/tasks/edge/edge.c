/** @file edge.c
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

	//test back to back time calls are equal
	long t1 = time();
	long t2 = time();
	printf("Testing edge case 1...");
	if(t1 == t2){
		printf("successful!\n");
	}
	else{
		printf("unsuccessful!\n");
	}

	//test that time recognizes a difference when sleeping for just 1 millisecond 
	t1 = time();
	sleep(1);
	t2 = time();

	printf("Testing edge case 2...");
	if(t1 != t2){
		printf("successful!\n");
	}
	else{
		printf("unsuccessful!\n");
	}

	//run this with a different timer to compare accuracy - we tested with stopwatch and found
	//it to be exact
	
	printf("Testing lag over 1 minute interval...");
	sleep(500);
	printf("Ready...");
	sleep(1000);
	printf("Set...");
	sleep(1000);
	printf("Go!\n");
	sleep(60000);
	printf("Stop!");
	return 0;


}

