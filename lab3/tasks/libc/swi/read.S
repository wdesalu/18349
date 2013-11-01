/** @file read.S
 *
 * @brief read sycall wrapper
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:53:16 -0400
 * 
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-29
 */

#include <asm.h>
#include <bits/swi.h>

	.file "read.S"
	.text
	.global read


read:
	stmfd	sp!, {r4, r5, r6}
	swi	READ_SWI
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
