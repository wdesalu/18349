#include <arm/timer.h>
#include <exports.h>

void sleep(int ms) {
//	unsigned int end_time = get_clock() + (unsigned int) ms;
//	volatile unsigned int *loop = get_vclock();i
	unsigned int start_time = sys_time;
	unsigned int end_time = sys_time + (unsigned int) ms;
	while (1) {
		if(sys_time > end_time){
			printf("done sleeping: %lu seconds \n" , sys_time - start_time);
			return;
		}
	}
//	printf("%d\n", ms);
}
