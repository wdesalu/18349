/** @file irq_handler.c
 *
 * @Authors: Sara Roy <slroy@andrew.cmu.edu>
 *          Samantha Klonaris <sklonari@andrew.cmu.edu>
 *  	    Derek Miller <damiller@andrew.cmu.edu>
 * @Date: 11/4/20 
 */

#include <exports.h> 
#include <arm/psr.h>
#include <arm/reg.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <exports.h>


extern volatile long sys_time;

void irq_handler(){
	// Save registers	
	asm("STMFD	sp!, {r0-r7,r9-r12, lr}\n");

	// Mask IRQ
	asm("MRS ip, CPSR\n");
	asm("ORR ip, #0x80\n");
	asm("MSR CPSR, ip\n");

	// Restore r8 global data
	asm("LDR	ip, =global_data\n");
	asm("LDR	r8, [ip]\n");
     	
	// Get the pending interrupts
	uint32_t icpr = reg_read(INT_ICIP_ADDR);
	
	// Check that timer interrupt occured	
	if((icpr & 0x04000000) > 1){
		// Increcment the system time.
		sys_time ++;
        
       		// Handle IRQ by writing a 1 to the matched 0 register bit
        	reg_write(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);
        
		// Read thev alue of the current match register
		uint32_t matchReg = reg_read(OSTMR_OSMR_ADDR(0));

        	// Increment the match register ahead by one millisecond
        	reg_write(OSTMR_OSMR_ADDR(0), matchReg + 3250);
	}

	// unmask irq
	asm("MRS ip, CPSR\n");
	asm("BIC ip, #0x80\n");
	asm("MSR cpsr, ip\n");

	// Restore registers
	asm("LDMFD 	sp!, {r0-r7,r9-r12, lr}\n");
  
	// Return from irq
	asm("SUBS  pc, lr, #4\n");
}

