	.file "I_Handler.S"
	.extern C_IRQ_Handler
	.text

	@.comm 	saved_lr 4,4
	.global I_Handler
	@.global I_Handler_Cleanup

I_Handler:
	STMFD	sp!, {r0-r7, r9-r12, lr} @set up the stack
	@LDR	lr, =saved_lr	  @save lr
	MRS	r2, cpsr
	ORR	r2, #0x80
	MSR	cpsr, r2
	
	@LDR	r2, =saved_r8	  @saving addres of r8 to r2
	@LDR	r8, [r2]	  @storing value of r8 from address stored in r2
	BL	C_IRQ_Handler	  @initialize C_IRQ_Handler
	
I_Handler_Cleanup:
	MRS	r2, cpsr
	BIC	r2, #0x80
	MSR	cpsr, r2
 	LDMFD	sp!, {r0-r7, r9-r12, lr} @restore vars from stack
	@LDR	lr, =saved_lr
	SUBS	pc, lr, #4	  @return to U-Boot I_Handler Table
