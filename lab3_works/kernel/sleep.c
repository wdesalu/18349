#include <arm/timer.h>
#include <exports.h>

void sleep(int ms) {
	unsigned int end_time = sys_time + (unsigned int) ms;
	while (1) {
		if(sys_time > end_time){
			//done sleeping
			return;
		}
		//else check again
	}
}
