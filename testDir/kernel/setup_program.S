/* @file setup_program.S
 *
 * @ Setup the user stack and launch the user program
 *
 * @ Authors: Sara Roy <slroy@andrew.cmu.edu>
 * @          Samantha Klonaris <sklonari@andrew.cmu.edu>
 * @	      Derek Miller <damiller@andrew.cmu.edu>
 * @ Date: 11/4/12
 */

#include <bits/swi.h>

	.file	"setup_program.S"
	.text

	.global	setup_program
	
	.type setup_program, %function

setup_program:
	@@ Restore clobbered r0 and r1 and save callee saved regs
	STMFD	sp!, {r4-r7, r9-r11,lr}
	LDR	ip, =global_data
	STR 	r8, [ip]

	@@ Save stack ptr
	LDR	ip, =kernel_sp
	STR	sp, [ip]

	@@ Switch to user mode
	MRS	ip, CPSR
	MSR	SPSR, ip
	MSR 	CPSR, #0x10

	@@ Set user stack to 0xa3000000
	LDR	sp, =0xA3000000
	
	@@ Build user stack
	MOV	r5, #0
	STMFD   sp!, {r5}
	CMP	r0,	#0
	BEQ	go
	MOV	r4,	r0

	@@ Loop to add argv values
	push_args:
	SUBS	r0,	r0,	#1
	ADD	r2,	r1,	r0,	ASL #2
	LDR	r3,	[r2]
	STMFD	sp!, {r3}
	BNE	push_args

	@@ Push ptr on stack to argv so it is aa char**, then push argc
	MOV 	ip, sp
	STMFD	sp!, {ip}
	STMFD	sp!, {r4}

	@@ Launch user prog
	go:
	LDR	pc,	=0xA0000000

