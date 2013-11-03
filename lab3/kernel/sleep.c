#include <arm/timer.h>

void sleep(int ms) {
	unsigned int end_time = get_clock() + (unsigned int) ms;
	unsigned int *loop = get_vclock();
	while (*loop < end_time) {}
}
