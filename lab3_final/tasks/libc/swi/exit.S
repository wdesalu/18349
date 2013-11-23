/** @file exit.S
 *
 * @brief exit sycall wrapper
 * @Authors: lrbloch, kafisher, adesalu
 * @Date: 11/3/13
 */

#include <asm.h>
#include <bits/swi.h>

	.file "exit.S"
	.global exit

exit:
	swi	EXIT_SWI
