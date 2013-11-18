.global load_user_prog
.global exit_to_kernel

load_user_prog:
	STMFD	sp!, {r1-r7,r9-r11, lr}		@ store gp registers
	LDR	ip, =global_data		@ save r8
	STR	r8, [ip]
	LDR	ip, =kernel_sp			@ load sp from kernel
	STR	sp, [ip]			@ set sp to kernel's sp

	@user mode
	MRS	ip, cpsr 			@ grab cpsr
	BIC	ip, ip, #0xFF			@ clear out its last 2 bytes
	ADD	ip, ip, #0xD0			@ disable IRQ, FIQ, set bit 4 to 1 (user mode = 10000)
	MSR	cpsr, ip			@ put it back into cpsr
	LDR	sp, =0xA3000000			@ set sp to kernel code

	MOV	r4, r0   @storing r0 in r4 so r0 can be used in count down loop

 stack:	
	SUBS	r0, r0, #1 			@loop and add everything to the stack
	ADD	r2, r1, r0, ASL #2		@ r2 = r1 + 4*r0
	LDR	r3, [r2]			@ r3 = mem[r2]
	STMFD	sp!, {r3}			@ sp = r3
	BNE	stack				@ continue until r0 = 1
	STMFD	sp!, {r4}			@ sp = r4
	
start_user_prog:
	LDR	pc, =0xA0000000			@ set pc to user prog, launches user prog

exit_to_kernel:
	LDR	ip, =global_0			@ status: 0
	STR	r0, [ip]
	LDR	ip, =kernel_sp			@ load sp from kernel
	LDR	sp, [ip]			@ restore sp to kernel's sp
	LDMFD	sp!, {r1-r7,r9-r11, lr}		@ restore regs from stack
	MOV	pc, lr				@ return
