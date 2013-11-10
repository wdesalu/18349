/** @file sleep.S
 *
 * @brief sleep sycall wrapper
 *
 * @authors adesalu, kafisher, lrbloch
 * @date 11/3/13
 */

#include <asm.h>
#include <bits/swi.h>

	.file "time.S"
	.text
	.global time

FUNC(time)
	stmfd	sp!, {r1-r12, lr}
	swi	TIME_SWI
	ldmfd	sp!, {r1-r12, lr}
	mov	pc, lr
