/* @file sleep.S
 *
 * @ Wrapper for sleep sys call 
 *
 * @ Authors: Sara Roy <slroy@andrew.cmu.edu>
 * @          Samantha Klonaris <sklonari@andrew.cmu.edu>
 * @	      Derek Miller <damiller@andrew.cmu.edu>
 * @ Date: 11/4/12
 */


#include <asm.h>
#include <bits/swi.h>

	.file "sleep.S"

FUNC(sleep)
	SWI 	SLEEP_SWI	@ invoke sleep swi
	MOV	pc, lr		@ return to user program
