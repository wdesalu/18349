#include <exports.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include "S_Handler.h"
#include "load_user_prog.h"

uint32_t global_data;
int kernel_sp = 0;

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;

	unsigned long int oldInstr, oldInstr2, exitVal, *s_addr;
	unsigned long int *irq_addr, oldIrq, oldIrq2, *ubootIrqAddr;
	unsigned long int *pointer, *sp, *ubootSwiAddr;
	unsigned long int *irqPointer;

	pointer = (unsigned long int*) 0x08;
	irqPointer = (unsigned long int*) 0x18;
	sp = (unsigned long int*) 0xa2fffffc;

	oldInstr = *pointer;
	oldInstr2 = *(pointer+1);

	if((oldInstr & 0xfe1ff000) != 0xe41ff000) {
		return 0xbadc0de;
	}

	if((oldInstr & 0x00800000) == 0x00800000) 
		s_addr = (unsigned long int*) ((oldInstr & 0xfff) + 0x10);
	else
		s_addr = (unsigned long int*) (0x10 - (oldInstr & 0xfff));

	ubootSwiAddr = (unsigned long int*) *(s_addr);


	oldIrq = *irqPointer;
	oldIrq2 = *(irqPointer+1);

	if((oldIrq & 0xfe1ff000) != 0xe41ff000) {
		return 0xbadc0de;
	}

	if((oldIrq & 0x00800000) == 0x00800000)
		irq_addr = (unsigned long int*) ((oldIrq & 0xfff) + 0x10);
	else
		irq_addr = (unsigned long int*) (0x10 - (oldIrq & 0xfff));

	ubootIrqAddr = (unsigned long int*) *(irq_addr);

	*(ubootSwiAddr) = 0xe51ff004;
	*(ubootSwiAddr + 1) = (unsigned) &S_Handler;

	*(ubootIrqAddr) = 0xe51ff004;
	*(ubootIrqAddr+1) = (unsigned) &I_Handler;

	exitVal = (int)load_user_prog(argc, argv);

	*(ubootSwiAddr) = (unsigned long int) oldInstr;
	*(ubootSwiAddr + 1) = (unsigned long int) oldInstr2;

	*(ubootIrqAddr) = (unsigned long int) oldIrq;
	*(ubootIrqAddr+1) = (unsigned long int) oldIrq2;

	return exitVal;
}
