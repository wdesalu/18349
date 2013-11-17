#include <exports.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>



unsigned swi_handler();
int kernel_sp = 0;
int ret_val = 0;


uint32_t global_data;

int kmain(int argc, char** argv, uint32_t table){
	app_startup(); /* bss is valid after this point */
	global_data = table;

	asm("STMFD	sp!, {r0, r1}\n");

	unsigned int* vec = (unsigned int*)0x8;

	if((*vec & 0xe50FF000) != 0xe50FF000){
		printf("The instruction is not recognized.\n");
		return 0x0badc0de;
	}

	int sign = ((*vec & 0x00800000) == 0x00800000); // 1 is adding, 0 is subtracting
	unsigned int offset = *vec & 0x00000fff;

	if(sign == 1)
		vec = (unsigned int*)(0x10 + offset);
	else if(sign == 0)
		vec = (unsigned int*)(0x10 - offset);
	else
		return 0xbadc0de;

	unsigned int *ptr1 = (unsigned int*)*vec;
	unsigned int *ptr2 = ((unsigned int*)*vec) + 0x1;

	unsigned int save1 = *ptr1;
	unsigned int save2 = *ptr2;

	/*replace with a branch to our swi handler*/
	*ptr1 = 0xe51ff004;
	*ptr2 = (unsigned int)swi_handler;

	asm("LDMFD	sp!, {r0, r1}\n");
	

	asm(".global exit_to_kernel\n");
	asm("STMFD	sp!, {r4-r12,lr}\n");
	asm("LDR	r2, =kernel_sp\n");
	asm("STR	sp, [r2]\n");
	asm("MRS	r2, CPSR\n");
	asm("MSR	SPSR, r2\n");
	asm("AND	r2, #0x10\n");
	asm("ORR	r2, #0xC0\n");
	asm("MSR CPSR, r2\n");
	asm("LDR	sp, =0xA3000000\n");
	asm("STMFD	sp!, {r0,r1}\n");
	asm("LDR	pc,	=0xA0000000\n");
	
	asm("exit_to_kernel:\n");
	asm("LDR	r2, =ret_val\n");
	asm("STR	r0, [r2]\n");
	asm("LDR r0, =kernel_sp\n");
	asm("LDR	sp,	[r0]\n");
	asm("LDMFD	sp!, {r4-r12, lr}\n");

	/* restore original swi handler*/
	*ptr1 = save1;
	*ptr2 = save2;

	return ret_val;
}

