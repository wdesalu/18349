@ exit.S: exit sycall wrapper
@
@ Authors: lrbloch, kafisher, adesalu
@ Date:    11/3/13

#include <bits/swi.h>

	.file	"exit.S"
	.text

	.global	exit
exit:
	swi EXIT_SWI
