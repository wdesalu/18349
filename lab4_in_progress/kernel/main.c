/** @file main.c
 *
 * @brief kernel main
 *
 * @authors adesalu kafisher lrbloch
 *           
 *           
 * @date   
 */

#include <kernel.h>
#include <task.h>
#include <sched.h>
#include <device.h>
#include <assert.h>
#include <globals.h>
#include <exports.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <int_asm.h>
#include <arm/reg.h>
#include <S_Handler.h>
#include <I_Handler.h>
#include <init_irq.h>
#include <load_user_prog.h>
#include <globals.h>

uint32_t global_data;
int global_0 = 0;
int saved_lr = 0;
int kernel_sp = 0;
volatile unsigned long sys_time = 0;

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;

	unsigned long int oldSwi, oldSwi2, exitVal, *s_addr;
	unsigned long int *irq_addr, oldIrq, oldIrq2, *ubootIrqAddr, *ubootSwiAddr;
	uint32_t ICMR, ICLR, OIER, OSCR, OSMR, OSSR;


	oldSwi = *(unsigned long int *)SWI_PTR;
	oldSwi2 = *(unsigned long int *)(SWI_PTR+1);

	if((oldSwi & LDR_MASK) != GOOD_INSTRUCTION) {
		return BAD_CODE;
	}

	if((oldSwi & POSITIVE_OFFSET) == POSITIVE_OFFSET)
		s_addr = (unsigned long int*) ((oldSwi & OFFSET_MASK) + UBOOT_SWI_PC);
	else
		s_addr = (unsigned long int*) (UBOOT_SWI_PC - (oldSwi & OFFSET_MASK));

	ubootSwiAddr = (unsigned long int*) *(s_addr);

	oldIrq = * (unsigned long int *) IRQ_PTR;
	oldIrq2 = *(unsigned long int *)(IRQ_PTR + 1);

	if((oldIrq & LDR_MASK) != GOOD_INSTRUCTION) {
		return BAD_CODE;
	}

	if((oldIrq & POSITIVE_OFFSET) == POSITIVE_OFFSET)
		irq_addr = (unsigned long int*) ((oldIrq & OFFSET_MASK) + UBOOT_IRQ_PC);
	else
		irq_addr = (unsigned long int*) (UBOOT_IRQ_PC - (oldIrq & OFFSET_MASK));

	ubootIrqAddr = (unsigned long int*) *(irq_addr);
	*(ubootSwiAddr) = LDR_PC_OPCODE;
	*(ubootSwiAddr + 1) = (unsigned) &S_Handler;

	*(ubootIrqAddr) = LDR_PC_OPCODE;
	*(ubootIrqAddr+1) = (unsigned) &irq_wrapper; //int_asm

	ICMR = reg_read(INT_ICMR_ADDR);
	ICLR = reg_read(INT_ICLR_ADDR);
	OIER = reg_read(OSTMR_OIER_ADDR);
	OSMR = reg_read(OSTMR_OSMR_ADDR(0));
	OSCR = reg_read(OSTMR_OSCR_ADDR);
	OSSR = reg_read(OSTMR_OSSR_ADDR);

	// set osmr match reg bit to 1 for interrupts
	reg_write(INT_ICMR_ADDR, SET_ICMR_M0_IRQ);
	//make interrupts irq
	reg_write(INT_ICLR_ADDR, 0x0);
	// set match reg
	reg_write(OSTMR_OSMR_ADDR(0), OSTMR_FREQ_VERDEX/FREQ_MS_FACTOR);
	// enable os timer interrupt for match 0 reg
	reg_write(OSTMR_OIER_ADDR, OSTMR_OIER_E0);
	// set clock reg to 0
	reg_write(OSTMR_OSCR_ADDR, 0x0);
	//clear status reg
	reg_write(OSTMR_OSSR_ADDR, 0x0);
	init_irq();
	
	exitVal = (int)load_user_prog(argc, argv);
	
	*(ubootSwiAddr) = (unsigned long int) oldSwi;
	*(ubootSwiAddr + 1) = (unsigned long int) oldSwi2;

	*(ubootIrqAddr) = (unsigned long int) oldIrq;
	*(ubootIrqAddr+1) = (unsigned long int) oldIrq2;

	// restore interrupt registers
	reg_write(INT_ICMR_ADDR, ICMR);
	reg_write(INT_ICLR_ADDR, ICLR);
	reg_write(OSTMR_OIER_ADDR, OIER);
	reg_write(OSTMR_OSSR_ADDR, OSSR);
	reg_write(OSTMR_OSCR_ADDR, OSCR);
	reg_write(OSTMR_OSMR_ADDR(0), OSMR);
	return exitVal;

	assert(0); 	/* should never get here */
}
