.global load_user_prog
.global exit_to_kernel
load_user_prog:
	STMFD	sp!, {r1-r12, lr}	@ store gp registers
	LDR	r2, =kernel_sp		@ load sp from kernel
	STR	sp, [r2]		@ set sp to kernel's sp
	
	MRS	r3, cpsr 		@ grab cpsr
	BIC	r3, r3, #0xFF		@ clear out its last 2 bytes
	ADD	r3, r3, #0xD0		@ disable IRQ, FIQ, set bit 4 to 1 (user mode = 10000)
	MSR	cpsr, r3		@ put this val into cpsr
	LDR	sp, =0xA3000000		@ set sp to kernel code
	MOV	r4, r0   		@ free r0 for use in countdown

 stack:	
	SUBS	r0, r0, #1 		@ loop and add everything to the stack
	ADD	r2, r1, r0, ASL #2	@ r2 = r1 + 4*r0
	LDR	r3, [r2]		@ r3 = mem[r2]
	STMFD	sp!, {r3}		@ sp = r3
	BNE	stack			@ keep going until r0 = 1
	STMFD	sp!, {r4}		@ sp = r4

start:
	LDR	pc, =0xa2000000		@ set pc to user prog, launches user prog

exit_to_kernel:
	LDR	r2, =kernel_sp		@ load sp from kernel
	LDR	sp, [r2]		@ restore sp to kernel's sp
	LDMFD	sp!, {r1-r12, lr}	@ restore stack
	MOV	pc, lr			@ return
