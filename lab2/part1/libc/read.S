@ read.S: read sycall wrapper
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date
#include <bits/swi.h>
	.file	"read.S"
	.text

	.global	read
read:
        stmfd   sp!, {r4, r5, r6}
        swi     READ_SWI
        cmp     r0, #0
        bge     .done

.error:
        ldr     r2, =errno
        mov     r1, #-1
        mul     r1, r0, r1
        str     r1, [r2]
        mov     r0, #-1

.done:
        ldmfd   sp!, {r4, r5, r6}
        mov     pc, lr
