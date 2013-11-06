	.file "I_Handler.S"
	.extern C_IRQ_Handler
	.text

	.global I_Handler

I_Handler:
	STMFD	sp!, {r0-r12, lr}
	LDR	r2, =saved_r8
	LDR	r8, [r2]
	BL	C_IRQ_Handler
 	LDMFD	sp!, {r0-r12, lr}
	SUBS	pc, lr, #4
