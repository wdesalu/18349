.global initIRQ

initIRQ:
	@STMFD	sp!, {r1-r12, lr}
	@LDR	r2, =kernel_sp
	@STR	sp, [r2]

	@MRS	r3, cpsr @change mode
	@BIC	r3, r3, #0xFF
	@ADD	r3, r3, #0xD0
	@MSR	cpsr, r3
	@LDR	sp, =0xA3000000
	@MOV	r4, r0   @storing r0 in r4 so r4 can be used in count down loop

	@LDR	r2, =kernel_sp
	@LDR	sp, [r2]
	@LDMFD	sp!, {r1-r12, lr}
	@MOV	pc, lr

	MSR 	cpsr, #0x12
	MOV	sp, #0xa1000000
	MSR	cpsr, #0x13
