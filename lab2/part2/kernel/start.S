@ start.S: Kernel startup routine
@
@ Date:   Thurs, 24 Oct 2013 16:20:33 -0400

	.file	"start.S"
	.text

	.global	_start
_start:
	@ Branch immediately to main without altering the execution environment.
	@ This indirection is needed to guarantee that the program entry point is
	@ LOAD_ADDR (probably 0xa3000000) without placing strict
	@ requirements on the layout of kernel.c
	b	main
