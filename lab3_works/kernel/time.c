#include <arm/timer.h>
#include <exports.h>

unsigned long time() {
  //Gets the time in milliseconds since boot
  //return (unsigned long) time;
  	printf("inside time\n");
	return 123456;
}
