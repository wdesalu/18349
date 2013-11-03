/** @file sleep.S
 *
 * @brief sleep sycall wrapper
 *
 * @authors adesalu, kafisher, lrbloch
 * @date 11/3/13
 */

#include <asm.h>
#include <bits/swi.h>

	.file "sleep.S"
	.text
	.global sleep

FUNC(sleep)
	swi	SLEEP_SWI
	mov	pc, lr
