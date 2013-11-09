.global load_user_prog
.global exit_to_kernel
load_user_prog:
	STMFD	sp!, {r1-r12, lr}
	LDR	r2, =kernel_sp
	STR	sp, [r2]

	MRS	r3, cpsr @change mode
	BIC	r3, r3, #0xFF
	ADD	r3, r3, #0xD0
	MSR	cpsr, r3
	LDR	sp, =0xA3000000
	MOV	r4, r0   @storing r0 in r4 so r4 can be used in count down loop

 stack:	
	SUBS	r0, r0, #1 @loop and add everything to the stack
	ADD	r2, r1, r0, ASL #2
	LDR	r3, [r2]
	STMFD	sp!, {r3}
	BNE	stack
	STMFD	sp!, {r4}

start:
	LDR	pc, =0xa2000000

exit_to_kernel:
	LDR	r2, =kernel_sp
	LDR	sp, [r2]
	LDMFD	sp!, {r1-r12, lr}
	MOV	pc, lr
