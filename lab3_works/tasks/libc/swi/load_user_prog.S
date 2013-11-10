.global load_user_prog
.global exit_to_kernel
@.global start_user_prog

load_user_prog:
	STMFD	sp!, {r1-r7,r9-r11, lr}
	LDR	ip, =global_data
	STR	r8, [ip]
	LDR	ip, =kernel_sp
	STR	sp, [ip]

	@irq mode
	@MRS	r3, cpsr
	@BIC	r3, r3, #0xFF
	@ADD	r3, r3, #0xD9 @no fucking idea what this should be
	@MSR	cpsr, r3
	@MSR	cpsr, #0x12
	@LDR	sp, =0xA1000000
	@MSR	cpsr, #0x13

	@user mode
	MRS	ip, cpsr @change mode
	BIC	ip, ip, #0xFF
	ADD	ip, ip, #0xD0
	MSR	cpsr, ip
	LDR	sp, =0xA3000000

	MOV	r4, r0   @storing r0 in r4 so r0 can be used in count down loop

 stack:	
	SUBS	r0, r0, #1 @loop and add everything to the stack
	ADD	r2, r1, r0, ASL #2
	LDR	r3, [r2]
	STMFD	sp!, {r3}
	BNE	stack
	STMFD	sp!, {r4}
	@B	exit_to_kernel
	
start_user_prog:
	LDR	pc, =0xA0000000

exit_to_kernel:
	LDR	ip, =global_0
	STR	r0, [ip]
	LDR	ip, =kernel_sp
	LDR	sp, [ip]
	LDMFD	sp!, {r1-r7,r9-r11, lr}
	MOV	pc, lr
