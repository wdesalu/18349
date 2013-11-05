@ authors: adesalu, kafisher, lrbloch
@ date: 11/3/13
	
.file "Set_Timer_Regs.S"
	.text
	
	.global Set_Timer_Regs

Set_Timer_Regs:
	LDR	r2, [r0]		@r2 = icmr
	LDR	r3, [r1]		@r3 = iclr
	BIC	r2, =0x3C000000		@clear out bits 29-26 in r2
	ADD	r2, =0x3C000000		@set bits 29-26 to 1
	BIC	r3, =0x3C000000		@clear out bits 29-26 in r3
	ADD	r3, =0x3C000000		@set bits 29-26 to 1
	STR	r2, r0			@put r2 into *icmr
	STR 	r3, r1			@put r3 into *iclr
	MOVS	pc, lr			@return from handler
