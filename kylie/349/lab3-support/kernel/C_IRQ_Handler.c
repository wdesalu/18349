#include <exports.h>
#include <types.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>

void C_IRQ_Handler() {
//	printf("In C_IRQ_Handler... Timer is: %d\n", get_clock());
	uint32_t next_time;
//	printf("a");

	if((reg_read(INT_ICIP_ADDR) & 0x04000000) > 1) {
		printf("do you get here???\n");
		addTimer(1);

		next_time = reg_read(OSTMR_OSMR_ADDR(0)) + 3250;
		//increment match register by one ms
		reg_write(OSTMR_OSMR_ADDR(0), next_time);
		//irq
		reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);
	}
	return;
}

