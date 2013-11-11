 /*
 * swi_handler.S
 *
 * Authors: Sara Roy <slroy@andrew.cmu.edu>
 *          Samantha Klonaris <sklonari@andrew.cmu.edu>
 *  	    Derek Miller <damiller@andrew.cmu.edu>
 * Date: 10/26/12
 */

	.file	"swi_handler.S"
FUNC(swi_handler)
	LDR r8, [sp, #20]
	STMFD	sp!,	{r1-r12,lr}
	
	LDR	r4,	[lr, #-4]
	BIC	r4, r4, #0xFF000000

exit_h:
	LDR	r5,  =0x900001
	CMP	r4, r5
	BEQ	exit_to_kernel

read_h:
	LDR	r5,  =0x900003
	CMP	r4, r5
	BNE     write_h  
	BLEQ	read
	B	end  

write_h:
	LDR	r5,  =0x900004
	CMP	r4, r5          
	BNE	invalid         
 	BLEQ	write           
    	B	end

invalid:
	LDR	r0, message
	BL	puts          
	LDR	r0, =0x0badc0de
	B	exit_to_kernel

end:
	LDMFD	sp!, {r1-r12, lr}
	MOVS	pc, lr
	
message:
	.word		err_mes
	.section 	.rodata
	
err_mes:
	.ascii	"Invalid system call\n"
