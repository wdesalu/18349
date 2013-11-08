	.file "I_Handler.S"
	.extern C_IRQ_Handler
	.text

	.global I_Handler

I_Handler:
	STMFD	sp!, {r0-r12, lr} @set up the stack
	LDR	r2, =saved_r8	  @saving addres of r8 to r2
	LDR	r8, [r2]	  @storing value of r8 from address stored in r2
	BL	C_IRQ_Handler	  @initialize C_IRQ_Handler
 	LDMFD	sp!, {r0-r12, lr} @restore stack
	SUBS	pc, lr, #4	  @return to U-Boot SWI Handler Table
