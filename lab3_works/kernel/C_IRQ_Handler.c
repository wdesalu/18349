#include <exports.h>
#include <types.h>
#include <I_Handler.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>

extern volatile unsigned long sys_time;

void C_IRQ_Handler() {
  	//printf("In C_IRQ_Handler\n");
	uint32_t next_time;

	//	unsigned int icpInt = reg_read(INT_ICIP_ADDR);
	//	printf("icpInt: %x\n", icpInt);
	volatile uint32_t OSCR = reg_read(OSTMR_OSCR_ADDR);
//	uint32_t OSMR = reg_read(OSTMR_OSMR_ADDR(0));
//	uint32_t OSSR = reg_read(OSTMR_OSSR_ADDR);

//	printf("OSCR: %d, OSMR: %d, OSSR: %d\n", OSCR, OSMR, OSSR);

//	if(reg_read(OSTMR_OSSR_ADDR) == 1)
//	{
//		printf("\n\n\n\ndo you get here???\n\n\n\n");
		
		//Incrementing by 10 milliseconds
		//addTimer(10);
		sys_time += 10;
		//printf("sys_time = %lu\n", sys_time);

		//Increment Match Register
		next_time = OSCR + (OSTMR_FREQ_VERDEX/100);
//		printf("New OSMR: %d\n", next_time);

		//Store incremented value
		reg_write(OSTMR_OSMR_ADDR(0), next_time);
		
		//irq
		reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);
//	}
	//return;
//	printf("\n leaving C_IRQ_handler\n");
//	I_Handler_Cleanup();
	return;
}
