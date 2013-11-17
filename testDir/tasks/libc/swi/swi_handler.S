/* @file swi_handler.S
 *
 * @ SWI handler 
 *
 * @ Authors: Sara Roy <slroy@andrew.cmu.edu>
 * @          Samantha Klonaris <sklonari@andrew.cmu.edu>
 * @	      Derek Miller <damiller@andrew.cmu.edu>
 * @ Date: 11/4/12
 */

#include <bits/swi.h>

	.file	"swi_handler.S"
	.text

	.global	swi_handler
	.type swi_handler, %function

swi_handler:	
	@ Save callee saved registers
	STMFD	sp!,	{r4-r12,lr}
	
	@ Restore r8 global data
	LDR	ip, =global_data
	LDR	r8, [ip]			
	
	@ Unmask IRQs
	MRS ip, CPSR
	BIC ip, #0x80
	MSR cpsr, ip
	
	@ Get the swi number
	LDR	r4,	[lr, #-4]
	BIC	r4, 	r4, #0xFF000000

	
@@ The following is basically a switch statement 
@@ for the different swi numbers

exit_h:
	LDR	r5,  =EXIT_SWI
	CMP	r4, r5
	BEQ	exit_to_kernel

read_h:
	LDR	r5,  =READ_SWI
	CMP	r4, r5
	BNE     write_h  
	BLEQ	read
	B	end  

write_h:
	LDR	r5,  =WRITE_SWI
	CMP	r4, r5          
	BNE	time_h         
 	BLEQ	write           
    	B	end

time_h:
	LDR	r5,  =TIME_SWI
	CMP	r4, r5          
	BNE	sleep_h         
 	BLEQ	time          
    	B	end

sleep_h:
	LDR	r5,  =SLEEP_SWI
	CMP	r4, r5          
	@BNE	invalid         
 	BLEQ	sleep          
    	B	end


@@ If execution gets here then the swi call is invalid
invalid:
	LDR	r0, message
	MOV	r1, r4
	BL	printf          
	LDR	r0, =0x0badc0de
	B	exit_to_kernel


@@ After the swi call returns, return to user program
end:	
	@ Restore calle saved registers
	LDMFD	sp!, {r4-r12, lr}
	MOVS	pc, lr


@@ Message to display to STD_OUT if swi call is invalid
message:
	.word		err_mes
	.section 	.rodata
	
err_mes:
	.ascii	"Invalid system call: %x\n"


