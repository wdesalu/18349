#include <S_Handler.h>
#include <exports.h>
#include <bits/swi.h>
#include <arm/timer.h>

void exit(int status);
ssize_t read(int fd, void* buf, size_t count);
ssize_t write(int fd, void* buf, size_t count);
void sleep(int s);
extern volatile unsigned long sys_time;

void C_SWI_Handler(unsigned swi_num, unsigned *regs)
{
	printf("in C_SWI_Handler.\n");
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
		case TIME_SWI:
			//printf("time swi\n");
			//regs[0] = sys_time;
			//printf("sys_time = %u\n", regs[0]);
			regs[0] = 12345;
			printf("time_swi\n");
			break;
		case SLEEP_SWI:
			sleep((int)regs[0]);
			break;
		default: 
			exit(-1); 
			break;
	}
	printf("leaving C_SWI_Handler\n");
}
