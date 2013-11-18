/** @file crt0.S
 *
 * @brief Execution startup routine
 *
 * @ Authors: Sara Roy <slroy@andrew.cmu.edu>
 * @          Samantha Klonaris <sklonari@andrew.cmu.edu>
 * @	   	  Derek Miller <damiller@andrew.cmu.edu>
 * @ Date: 10/26/20  
 *
 * @ Authors: Sara Roy <slroy@andrew.cmu.edu>
 * @          Samantha Klonaris <sklonari@andrew.cmu.edu>
 * @	   	  Derek Miller <damiller@andrew.cmu.edu>
 * @ Date: 10/26/20  
 */

#include <asm.h>
#include <bits/swi.h> 

	.file	"crt0.S"

	.global	_start

FUNC(_start)
	ldr r0, [sp] 			@ load argc into r0
	ldr r1, [sp, #4] 		@ load argv into r1
	bl main					@ call main function
	swi EXIT_SWI			@ exit if main returns

