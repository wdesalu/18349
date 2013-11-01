/*
 * kernel.c: Kernel main (entry) function
*
 * Author: Laura Bloch <lrbloch@andrew.cmu.edu>
 *         Wale Desalu <adesalu@andrew.cmu.edu>
 *	   Kylie Fisher <kafisher@andrew.cmu.edu>
 * Date:   10/23 21:13
 */

//Imported Libraries
#import "include/bits/errno.h"
#import "include/bits/fileno.h"
#import "include/bits/swi.h"
#import	"S_Handler.h"
#import "load_user_prog.h"
#include <exports.h>

int kernel_sp = 0;

int main(int argc, char *argv[]) {
	unsigned long int *pointer;
	unsigned long int *sp;
	unsigned long int oldInstr;
	unsigned long int oldInstr2;
	unsigned long int * ubootJumpAddr;
	unsigned long int * ubootSwiAddr;
	unsigned long int s_addr;
	unsigned long int exitVal;
	
	//go to 0x08: location of LDR command (vector table)
	pointer = (unsigned long int *) 0x08;
	//stack pointer points to top of kernel space
	sp = (unsigned long int *) 0xa2fffffc;
	//store current instructions at vector table
	oldInstr = *pointer;
	oldInstr2 = *(pointer+1);

	// verify that oldInstr & 0xfffff000 corresponds to ldr pc [pc, #imm12]
	// ignore the don't cares (hence 0xfe1ff000 instead of 0xfffff000)
	if((oldInstr & 0xfe1ff000) != 0xe41ff000) {
		// bad instruction!
		return 0xbadc0de;
	}

	// use *pointer to get address of UBoot's SWI Handler	
	// get pos/neg offset by checking oldInstr & 0x00800000 
	// store oldInstr +/- offset as the address of the jump table entry
	if((oldInstr & 0x00800000) == 0x00800000){
		ubootJumpAddr = (unsigned long int *) ((oldInstr & 0xfff) + 0x10);
	}
	else{ 
		ubootJumpAddr = (unsigned long int *)( 0x10 - (oldInstr & 0xfff));
	}

	//Find Address of SWI Handler
	ubootSwiAddr = (unsigned long int*) *(ubootJumpAddr);
	
	// grab address of our S_Handler
	s_addr = (unsigned) &S_Handler;
	
	//at ubootSwiAddr put in LDR pc, [pc, #-4] at beginning of Uboot Swi Handler
	*(ubootSwiAddr) = 0xe51ff004;

	//put in s_addr at the next address where &S_Handler should be
	*(ubootSwiAddr + 1) = s_addr;

	// call assembly function
	exitVal = (int)load_user_prog(argc, argv);
	
	// restore data at ubootSwiAddr & ubootSwiAddr + 1
	*(ubootSwiAddr) = (unsigned long int) oldInstr;
	*(ubootSwiAddr + 1) = (unsigned long int) oldInstr2;
	return exitVal;
}
