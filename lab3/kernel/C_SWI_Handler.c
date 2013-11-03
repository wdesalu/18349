/*
 * authors: adesalu, kafisher, lrbloch
 * date: 11/3/13
 */
#include <S_Handler.h>
#include <exports.h>
#include <bits/swi.h>

void exit(int status);
ssize_t read(int fd, void* buf, size_t count);
ssize_t write(int fd, void* buf, size_t count);


void C_SWI_Handler(unsigned swi_num, unsigned *regs)
{
	switch (swi_num){
		case  EXIT_SWI: 
			exit(*regs);
			break;
		case  READ_SWI: 
			regs[0] = read((int)regs[0], (void*)regs[1], (size_t)regs[2]);
			break;
		case  WRITE_SWI: 
			regs[0] = write((int)regs[0], (void*)regs[1], (size_t)regs[2]);
			break;
/*		case TIME_SWI:
			regs[0] = time();
			break;
		case SLEEP_SWI:
			regs[0] = sleep((int)regs[0]);
			break; */
		// undefined: exit with status -1
		default: 
			exit(-1); 
			 break;
	}
}
