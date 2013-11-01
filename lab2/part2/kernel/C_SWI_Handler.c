/*
#include "write.c"
#include "read.c"
#include "exit.c"
*/
#include "S_Handler.h"
#include <exports.h>
void exit(int status);
ssize_t read(int fd, void* buf, size_t count);
ssize_t write(int fd, void* buf, size_t count);


void C_SWI_Handler(unsigned swi_num, unsigned *regs)
{
	switch (swi_num){
		// 0x900001 = exit swi_num
		case  0x900001: 
			exit(*regs);
			break;
		// 0x900003 = read swi_num
		case  0x900003: 
			regs[0] = read((int)regs[0], (void*)regs[1], (size_t)regs[2]);
			break;
		// 0x900004 = write swi_num
		case  0x900004: 
			regs[0] = write((int)regs[0], (void*)regs[1], (size_t)regs[2]);
			break;
		// undefined: exit with status -1
		default: 
			exit(-1); 
			 break;
	}
}
