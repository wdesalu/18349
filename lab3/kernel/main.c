#include <exports.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>

uint32_t global_data;
int kernel_sp = 0;

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;

	unsigned long int oldInstr oldInstr2, exitVal, s_addr;
	unsigned long int *pointer, *sp, *ubootJumpAddr, *ubootSwiAddr;

	pointer = (unsigned long int*) 0x08;
	sp = (unsigned long int*) 0xa2fffffc;

	oldInstr = *pointer;
	oldInstr2 = *(pointer+1);

	if((oldInstr & 0xfe1ff000) != 0xe41ff000) {
		return 0xbadc0de;
	}

	if((oldInstr & 0x00800000) == 0x00800000) 
		ubootJumpAddr = (unsigned long int*) ((oldInstr & 0xfff) + 0x10);
	else
		ubootJumpAddr = (unsigned long int*) (0x10 - (oldInstr & 0xfff));

	ubootSwiAddr = (unsigned long int*) *(ubootJumpAddr);

	s_addr = (unsigned) &S_Handler;

	*(ubootSwiAddr) = 0xe51ff004;
	*(ubootSwiAddr + 1) = s_addr;

	exitVal = (int)load_user_prog(argc, argv);

	*(ubootSwiAddr) = (unsigned long int) oldInstr;
	*(ubootSwiAddr + 1) = (unsigned long int) oldInstr2;

	return exitVal;
}
