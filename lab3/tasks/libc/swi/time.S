/** @file time.S
 *
 * @brief time sycall wrapper
 * @authors: adesalu, kafisher, lrbloch
 * @date: 11/3/13
 *
 */

#include <asm.h>
#include <bits/swi.h>

	.file "time.S"
	.text
	.global time

FUNC(time)
	swi	TIME_SWI
	mov	pc, lr
