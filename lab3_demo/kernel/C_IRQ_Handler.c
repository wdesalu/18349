#include <exports.h>
#include <types.h>
#include <I_Handler.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <globals.h>

extern volatile unsigned long sys_time;

void C_IRQ_Handler() {

	uint32_t next_time;

	volatile uint32_t OSCR = reg_read(OSTMR_OSCR_ADDR);
	volatile uint32_t OSSR = reg_read(OSTMR_OSSR_ADDR);

	//If an Interrupt has been received
	if(OSSR == 1)
	{
		//add 10 milliseconds
		sys_time += TIME_INCR;

		//Increment Match Register
		next_time = OSCR + (OSTMR_FREQ_VERDEX/FREQ_MS_FACTOR);

		//Store incremented value
		reg_write(OSTMR_OSMR_ADDR(0), next_time);
		
		//clear OSSR; interrupt handled
		reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);

		while (reg_read(OSTMR_OSMR_ADDR(0)) < OSCR){
			next_time = OSCR + (OSTMR_FREQ_VERDEX/FREQ_MS_FACTOR);
			reg_write(OSTMR_OSMR_ADDR(0), next_time);
		}
	}
	return;
}
