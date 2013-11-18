#include <S_Handler.h>
#include <exports.h>
#include <bits/swi.h>
#include <arm/timer.h>
#include <globals.h>
<<<<<<< HEAD:lab4/kernel/arm/C_SWI_Handler.c
#include <C_SWI_Handler.h>
=======
#include <syscalls.h>
>>>>>>> upstream/master:lab3_works/kernel/C_SWI_Handler.c

extern volatile unsigned long sys_time;

void C_SWI_Handler(unsigned swi_num, unsigned *regs)
{
	switch (swi_num){
<<<<<<< HEAD:lab4/kernel/arm/C_SWI_Handler.c
=======
		case  EXIT_SWI: 
			exit(*regs);
			break;
>>>>>>> upstream/master:lab3_works/kernel/C_SWI_Handler.c
		case  READ_SWI: 
			regs[0] = read((int)regs[0], (void*)regs[1], (size_t)regs[2]);
			break;
		case  WRITE_SWI: 
			regs[0] = write((int)regs[0], (void*)regs[1], (size_t)regs[2]);
			break;
		case TIME_SWI:
			regs[0] = (unsigned) sys_time;
			break;
		case SLEEP_SWI:
			sleep((int)regs[0]);
			break;
		default: 
<<<<<<< HEAD:lab4/kernel/arm/C_SWI_Handler.c
=======
			exit(-1); 
>>>>>>> upstream/master:lab3_works/kernel/C_SWI_Handler.c
			break;
	}
}
