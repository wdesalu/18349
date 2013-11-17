/* @file time.S
 *
 * @ Sytem call wrapper for time
 *
 * @ Authors: Sara Roy <slroy@andrew.cmu.edu>
 * @          Samantha Klonaris <sklonari@andrew.cmu.edu>
 * @	      Derek Miller <damiller@andrew.cmu.edu>
 * @ Date: 11/4/12
 */

#include <asm.h>
#include <bits/swi.h>

	.file "time.S"

FUNC(time)
	SWI 	TIME_SWI	@ Invoke the Swi call
	MOV 	pc, lr		@ return to user program when done

