/* @file exit.S
 *
 * @ Setup the user stack and launch the user program
 *
 * @ Authors: Sara Roy <slroy@andrew.cmu.edu>
 * @          Samantha Klonaris <sklonari@andrew.cmu.edu>
 * @	      Derek Miller <damiller@andrew.cmu.edu>
 * @ Date: 11/4/12
 */

#include <bits/swi.h>

	.file	"exit.S"
	.text

	.global	_start
_start:
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@ Must use fatload to run program	@
	@ Kermit does not load this program	@
        @ right due to alignment issues.	@
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	mov	r0, #42
	swi	EXIT_SWI
