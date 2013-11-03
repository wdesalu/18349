/** @file write.S
 *
 * @brief write sycall wrapper
 *
 * @authors: lrbloch, kafisher, adesalu
 * @date 2013-11-03
 */

#include <asm.h>
#include <bits/swi.h>

	.file "write.S"
	.text
	.global write

write:
	stmfd	sp!, {r4, r5, r6}
	swi	WRITE_SWI
	cmp	r0, #0
	bge	.done

.error:
	ldr	r2, =errno
	mov	r1, #-1
	mul	r1, r0, r1
	str	r1, [r2]
	mov	r0, #-1

.done:
	ldmfd	sp!, {r4, r5, r6}
	mov	pc, lr
