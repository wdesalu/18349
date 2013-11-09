#include <exports.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <S_Handler.h>
#include <I_Handler.h>
#include <init_irq.h>
#include <load_user_prog.h>

uint32_t global_data;
int global_0 = 0;
int saved_lr = 0;
int kernel_sp = 0;

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;

	unsigned long int oldInstr, oldInstr2, exitVal, *s_addr;
	unsigned long int *irq_addr, oldIrq, oldIrq2, *ubootIrqAddr;
	unsigned long int *pointer, *ubootSwiAddr;
	unsigned long int *irqPointer;
	uint32_t ICMR, ICLR, OIER;


	pointer = (unsigned long int*) 0x08;
	irqPointer = (unsigned long int*) 0x18;
	initializeTimer();

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

	printf("hello");
	if((oldIrq & 0xfe1ff000) != 0xe41ff000) {
		return 0xbadc0de;
	}

	if((oldIrq & 0x00800000) == 0x00800000)
		irq_addr = (unsigned long int*) ((oldIrq & 0xfff) + 0x20);
	else
		irq_addr = (unsigned long int*) (0x20 - (oldIrq & 0xfff));

	//irq_addr = (unsigned long int *) 0x34;
	ubootIrqAddr = (unsigned long int*) *(irq_addr);
	printf("irqAddr = %x\n", (unsigned int) irq_addr);	
	printf("ubootIrqAddr = %x\n", (unsigned int) ubootIrqAddr);
	*(ubootSwiAddr) = 0xe51ff004;
	*(ubootSwiAddr + 1) = (unsigned) &S_Handler;

	*(ubootIrqAddr) = 0xe51ff004;
	*(ubootIrqAddr+1) = (unsigned) &I_Handler;

	//printf("hey");
	ICMR = reg_read(INT_ICMR_ADDR);
	ICLR = reg_read(INT_ICLR_ADDR);
	OIER = reg_read(OSTMR_OIER_ADDR);

	// set osmr match reg bit to 1 for interrupts
	reg_write(INT_ICMR_ADDR, 0x04000000);
	//make interrupts irq
	reg_write(INT_ICLR_ADDR, 0x0);
	// set match reg
	reg_write(OSTMR_OSMR_ADDR(0), OSTMR_FREQ_VERDEX/1000);
	// enable os timer interrupt for match 0 reg
	reg_write(OSTMR_OIER_ADDR, OSTMR_OIER_E0);
	// set clock reg to 0
	reg_write(OSTMR_OSCR_ADDR, 0x0);
	//clear status reg
	reg_write(OSTMR_OSSR_ADDR, 0x0);
	//printf("tit");
	printf("OSCR = %d\n", reg_read(OSTMR_OSCR_ADDR));	
	printf("loading user program\n");
	//load_user_prog(argc, argv);
	//printf("user program loaded: initializing irq.\n");
	init_irq();
	printf("irq initialized, starting user program. \n");
//	load_user_prog(argc, argv);
	
	exitVal = (int)load_user_prog(argc, argv);
	printf("user program finished. \n");
	*(ubootSwiAddr) = (unsigned long int) oldInstr;
	*(ubootSwiAddr + 1) = (unsigned long int) oldInstr2;

	*(ubootIrqAddr) = (unsigned long int) oldIrq;
	*(ubootIrqAddr+1) = (unsigned long int) oldIrq2;

	// restore interrupt shit
	reg_write(INT_ICMR_ADDR, ICMR);
	reg_write(INT_ICLR_ADDR, ICLR);
	reg_write(OSTMR_OIER_ADDR, OIER);
	printf("\ncame back to main.c\n");
	return exitVal;
}

