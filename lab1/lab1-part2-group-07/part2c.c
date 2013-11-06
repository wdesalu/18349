/*
adesalu
lrbloch
kafisher */

#include <stdlib.h>
#include <stdio.h>

/**
 * Function: oddball
 * Description: Baseline implementation for finding the number that
 *   occurs only once in the array.
 * Arguments:
 *   arr - pointer to start of integer array
 *   len - number of elements in array
 * Return:
 *   The number that occurs only once
 */
#ifdef DEFAULT
int oddball(int *arr, int len) {
	int i, j;
	int foundInner;
	int result = 0;

	for (i = 0; i < len; i++) {
		foundInner = 0;
		for (j = 0; j < len; j++) {
			if (i == j) {
				continue;
			}
			if (arr[i] == arr[j]) {
				foundInner = 1;
			}
		}
		if (foundInner != 1) {
			result = arr[i];
		}
	}

	return result;
}
#endif

#ifdef OPTIMIZE1
/*
* Function: oddball (Optimization 1)
* Description: An optimized implementation which uses
* 	the fact that almost all integers are represented twice
*	and the summation identity applied in this case
*	can be used to calculate the result. The difference
*	of the summation of all integers from 1 to n
* 	inclusive with the given array returns the unique
*	value that differs from the arrays.
*
*	The for loop is a count down loop because it takes         
*       advantage of the ARM architecture and is more             
*       efficient than counting up. 
* Arguements:
*	arr - pointer to start of integer array
*	len - number of elements in array
* Return:
*	The number that occurs only once
*/
int oddball(int *arr, int len) {
	//Local Variables
	int n = (len+1)/2;	//Highest integer
	int sum1 = (n*n)+n;	//Summation of all integers doubled
	int sum2 = 0;		//Summation of integers in array
	int i;
	
	//Calculate the summation of integers
	for(i=len-1;i>=0;i--){
		sum2 = sum2+arr[i];	
	}

	//Calculate the oddball from difference of sums	
	return sum1-sum2;
}
#endif

#ifdef OPTIMIZE2
/*
* Function: oddball (Optimization 2)
* Description: An optimized implementation which
* 	uses the fact that when two numbers xor each
* 	other, the result is 0. When each element of
* 	the array is combined using xor, the duplicate
* 	elements become equal to 0 and the unique 
* 	element is returned.
*
* 	The for loop is a count down loop because it takes
*	 advantage of the ARM architecture and is more
* 	efficient than counting up.
* Arguments:
* 	arr - pointer to start of integer array
*	len - number of elements in array
* Return:
* 	The number that occurs only once
*/
int oddball(int *arr, int len) {
	int i, result = 0;

	for(i=len-1;i>0;i--){
		result ^= arr[i];
	}
	
	return result;
}
#endif

/**
 * Function: randGenerator
 * Description: Generate a random array that is in compliance with
 *   lab specification
 * Arguments:
 *   arr - pointer to start of integer array
 *   len - number of elements in array
 * Return:
 *   Unused, but feel free to utilize it.
 */

int randGenerator(int *arr, int len) {
	int i, j, r, rcount;
	for (i = 0; i < len; i++) {
		do {
			rcount = 0;
			r = rand()%(len/2 + 1) + 1;
			for (j = 0; j < i && rcount < 2; j++) {
				if (arr[j] == r) {
					rcount++;
				}
			}
		} while(rcount >= 2);
		arr[i] = r;
		printf("%d ", r);
	}
	printf("\nDone generating\n");
	return 0;
}




