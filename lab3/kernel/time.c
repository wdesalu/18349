#include <arm/timer.h>

unsigned long time() {

  //Gets the time in milliseconds since boot
  return get_clock();
}
