#include <S_Handler.h>
#include <exports.h>
#include <bits/swi.h>
#include <arm/timer.h>

void exit(int status);
ssize_t read(int fd, void* buf, size_t count);
ssize_t write(int fd, void* buf, size_t count);
void sleep(int s);
void time();
extern volatile unsigned long sys_time;

void C_SWI_Handler(unsigned swi_num, unsigned *regs)
{
//	printf("in C_SWI_Handler.\n");
	switch (swi_num){
		case  EXIT_SWI: 
//			printf("exit swi\n\n\n");
			exit(*regs);
			break;
		case  READ_SWI: 
//			printf("read swi\n\n\n");
			regs[0] = read((int)regs[0], (void*)regs[1], (size_t)regs[2]);
			break;
		case  WRITE_SWI: 
			//printf("write swi\n\n\n");
			regs[0] = write((int)regs[0], (void*)regs[1], (size_t)regs[2]);
			break;
		case TIME_SWI:
//			printf("time swi\n\n\n");
			regs[0] = (unsigned) sys_time;
//			printf("IN SWI: sys_time = %u\n", regs[0]);
			break;
		case SLEEP_SWI:
//			printf("sleep swi\n\n\n");
			sleep((int)regs[0]);
			break;
		default: 
//			printf("default swi (dne)\n\n\n");
			exit(-1); 
			break;
	}
//	printf("leaving C_SWI_Handler\n");
}
