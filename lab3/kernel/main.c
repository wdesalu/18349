/*
 *	authors: adesalu, kafisher, lrbloch
 *	date: 11/3/13
*/
#include <exports.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <S_Handler.h>
#include <load_user_prog.h>

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

	// go to 0x08: location of LDR command (vector table)
	pointer = (unsigned long int*) 0x08;
	//irq pointer points to 0x18
	irqPointer = (unsigned long int*) 0x18;
	//stack pointer points to top of kernel space
	sp = (unsigned long int*) 0xa2fffffc;

	//store current vector table instructions
	oldInstr = *pointer;
	oldInstr2 = *(pointer+1);

	// verify that oldInstr corresponds to ldr pc, [pc, #imm12]
	//ignore the don't cares (hence 0xfe1ff000 instead of 0xfffff000)
	if((oldInstr & 0xfe1ff000) != 0xe41ff000) {
		return 0xbadc0de;
	}

	/*
	 * use *pointer to get addr of UBoot's SWI Handler
	 * get pos/neg offset by checking oldInstr & 0x00800000
	 * store oldInstr +/- offset as addr of jump table entry
	 */

	if((oldInstr & 0x00800000) == 0x00800000) 
		s_addr = (unsigned long int*) ((oldInstr & 0xfff) + 0x10);
	else
		s_addr = (unsigned long int*) (0x10 - (oldInstr & 0xfff));

	// Find addr of SWI Handler
	ubootSwiAddr = (unsigned long int*) *(s_addr);

	// Store old IRQ instructions
	oldIrq = *irqPointer;
	oldIrq2 = *(irqPointer+1);
	
	// check that oldIRQ instruction corresponds to the right instr
	if((oldIrq & 0xfe1ff000) != 0xe41ff000) {
		return 0xbadc0de;
	}
	
	/*
	 * Use oldIRQ to get addr of UBoot's IRQ Handler
	 * get pos/neg offset
	 * use this to get addr of jump table entry
	*/
	if((oldIrq & 0x00800000) == 0x00800000)
		irq_addr = (unsigned long int*) ((oldIrq & 0xfff) + 0x10);
	else
		irq_addr = (unsigned long int*) (0x10 - (oldIrq & 0xfff));

	ubootIrqAddr = (unsigned long int*) *(irq_addr);
	
	// put LDR pc, [pc, #-4] at beginning of UBoot SwiHandler
	*(ubootSwiAddr) = 0xe51ff004;
	// put addr of our S_Handler at next line to load into pc
	*(ubootSwiAddr + 1) = (unsigned) &S_Handler;

	// put LDR pc, [pc, #-4] at beginning of IRQ SwiHandler
	*(ubootIrqAddr) = 0xe51ff004;
	// put addr of our I_Handler at next line to load into pc
	//*(ubootIrqAddr+1) = (unsigned) &I_Handler;

	// call assembly function to load usedr program
	exitVal = (int)load_user_prog(argc, argv);

	//restore data in the UBoot Vector Table
	*(ubootSwiAddr) = (unsigned long int) oldInstr;
	*(ubootSwiAddr + 1) = (unsigned long int) oldInstr2;

	//*(ubootIrqAddr) = (unsigned long int) oldIrq;
	//*(ubootIrqAddr+1) = (unsigned long int) oldIrq2;

	return exitVal;
}
