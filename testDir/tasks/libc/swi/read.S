/* @file read.S
 *
 * @ read system call wrapper 
 *
 * @ Authors: Sara Roy <slroy@andrew.cmu.edu>
 * @          Samantha Klonaris <sklonari@andrew.cmu.edu>
 * @	      Derek Miller <damiller@andrew.cmu.edu>
 * @ Date: 11/4/12
 */


#include <asm.h>
#include <bits/swi.h>


	.file "read.S"


FUNC(read)
	swi READ_SWI 		@ invoke syscall READ
	cmp r0, #0		@ compare the return value of read with 0
	bmi .error		@ if negative branch to error
	mov pc, lr			
	
	
.error:
	mov r2, #-1			
	mul r0, r2		@ get the positive value of r0
	ldr r1, =errno		
	str r0, [r1]		@ set global errno varaiable to error value
	mov r0, #-1		@ return -1
	mov pc, lr
