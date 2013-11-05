@ authors: adesalu, kafisher, lrbloch
@ date: 11/3/13
	
.file "Set_Timer_Regs.S"
	.text
	
	.global Set_Timer_Regs

Set_Timer_Regs:
	LDR	r3, [r0]		@r3 = icmr
	LDR	r4, [r1]		@r4 = iclr
	LDR 	r5, [r2]		@r5 = oier
	BIC	r3, =0x3C000000		@clear out bits 29-26 in r3
	ADD	r3, =0x3C000000		@set bits 29-26 to 1
	BIC	r4, =0x3C000000		@clear out bits 29-26 in r4
	ADD	r4, =0x3C000000		@set bits 29-26 to 1
	BIC	r5, =0x1		@clear out bit 0 in r5
	ADD	r5, =0x1		@set bit 0 to 1
	STR	r3, r0			@put r3 into *icmr
	STR 	r4, r1			@put r4 into *iclr
	STR	r5, r2			@put r5 into *oier
	MOVS	pc, lr			@return from handler
