#include <S_Handler.h>
#include <exports.h>
#include <bits/swi.h>
#include <arm/timer.h>
#include <globals.h>
#include <C_SWI_Handler.h>

extern volatile unsigned long sys_time;

void C_SWI_Handler(unsigned swi_num, unsigned *regs)
{
	switch (swi_num){
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
			break;
	}
}
