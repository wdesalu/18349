#include <arm/timer.h>
#include <arm/reg.h>

volatile uint32_t timer;


void startTimer() {
        timer = 0;
}

void addTimer() {
        timer++;
}

unsigned int get_clock() {
        return timer;
}

volatile unsigned int* get_vclock() {
        return &timer;
}

