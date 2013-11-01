@ hello.S: Hello world! in assembly
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date

#include <bits/swi.h>
	.file	"hello.S"
	.text

	.global	_start
_start:
	mov r0, $1
	ldr r1, =hello_str
	ldr r2, =hello_size
	swi	WRITE_SWI
	mov r0, #0
	swi	EXIT_SWI
hello_str:
	.ascii "Hello world!\n"
	.set hello_size, .-hello_str
