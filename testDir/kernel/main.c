/** @file main.c
 *
 * @Authors: Sara Roy <slroy@andrew.cmu.edu>
 *          Samantha Klonaris <sklonari@andrew.cmu.edu>
 *  	    Derek Miller <damiller@andrew.cmu.edu>
 * @Date: 11/4/20 
 */

#include <exports.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include "irq_handler.h"

unsigned swi_handler();
unsigned irq_handler();
int setup_program(int argc, char** argv);

int kernel_sp = 0;
int ret_val = 0;

uint32_t global_data;
uint32_t ICMR_init;
uint32_t ICLR_init;
uint32_t OIER_init;

int* install_handler(unsigned int vector, unsigned int location){
	
	// address of vector
	unsigned int* vec = (unsigned int*)vector;

	// return an error if vector is not a load instruction
	if((*vec & 0xe50FF000) != 0xe50FF000){
		printf("The instruction is not recognized.\n");
		return (int*)-1;
	}

	// mask to find sign bit (1 is adding, 0 is subtracting)
	int sign = ((*vec & 0x00800000) == 0x00800000); // 1 is adding, 0 is subtracting
	unsigned int offset = *vec & 0x00000fff;

	// Check the sign bit to either add or subtract offset
	if(sign == 1)
		vec = (unsigned int*)(vector + 8 + offset);
	else if(sign == 0)
		vec = (unsigned int*)(vector + 8 - offset);
	else
		return (int*)-1;//0xbadc0de;

	// store and save first instructions of original SWI handler to return later
	unsigned int* ptr1 = (unsigned int*)*vec;
	unsigned int* ptr2 = ((unsigned int*)*vec) + 0x1;
	
	int* array = malloc(sizeof(int)*4);
	array[0]= (int)ptr1;
	array[1] = (int)ptr2;
	array[2] = *ptr1;
	array[3] = *ptr2;

	// replace with a branch to location 
	*ptr1 = 0xe51ff004;
	*ptr2 = location;
	
	// return saved ptrs array
	return array;
}

void uninstall(int* array){
	// Replace our code with the original code
	*((int*)array[0]) = array[2];
	*((int*)array[1]) = array[3];
	
	free(array);
	return;
}

void initialize_IRQ(){	
	// Setup irq stack
	asm("MSR	CPSR, #0x12\n"); 	// switch to IRQ mode
	asm("MOV	sp, #0xa1000000\n"); 		// SP of irq stack
	asm("MSR	CPSR, #0x13\n"); 	// Switch back to supervisor
		
	// Save interrupt controller state
	ICMR_init = reg_read(INT_ICMR_ADDR);
        ICLR_init = reg_read(INT_ICLR_ADDR);
	OIER_init = reg_read(OSTMR_OIER_ADDR);		

	// Set OSMR matched reg bit to 1 so the interrupt is handled
        reg_write(INT_ICMR_ADDR, 0x04000000); 

	// Make interrupts IRQs
        reg_write(INT_ICLR_ADDR, 0x0);
	
	// Initialize OS timer
        sys_time = 0;
	
	// Set matched register
        reg_write(OSTMR_OSMR_ADDR(0), 3250);
	
	// Enable OS timer interrupt for matched 0 register
        reg_write(OSTMR_OIER_ADDR, OSTMR_OIER_E0);
	
	// Clear status register        
	reg_write(OSTMR_OSSR_ADDR, 0x0);
	
	// Set clock register to 0
	reg_write(OSTMR_OSCR_ADDR, 0x0);
}

int kmain(int argc, char** argv, uint32_t table){
	app_startup(); /* bss is valid after this point */
	global_data = table;
	
	// Install our handlers
	int* saved_swi = install_handler(0x8, (unsigned int)swi_handler);

	int* saved_irq = install_handler(0x18, (unsigned int)irq_handler);
	
	// Chec that the handlers succesfully installed
	if((int)saved_swi == -1 || (int)saved_irq == -1){
		free(saved_swi);
		free(saved_irq);
		return 0xbadc0de;
	}
	
	// Initialize the timer interrupt
	initialize_IRQ();
	
	// Setup the user program and stack
	setup_program(argc, argv);

	// Reinstall handlers
	uninstall(saved_swi);
	uninstall(saved_irq);
	
	// Restore interrupt controller registers
	reg_write(INT_ICMR_ADDR, ICMR_init);
        reg_write(INT_ICLR_ADDR, ICLR_init);
	reg_write(OSTMR_OIER_ADDR, OIER_init);	

	// Exit from kernel called from exit swi call
	asm(".global exit_to_kernel\n");
	asm("exit_to_kernel:\n");
	asm("LDR 	ip, =ret_val\n");
	asm("STR	r0,[ip]\n");
	asm("LDR 	ip, =kernel_sp\n");
	asm("LDR	sp,[ip]\n");
	asm("LDMFD	sp!, {r4-r7, r9-r11, lr}\n");

	// Return exit status
	return ret_val;
}

