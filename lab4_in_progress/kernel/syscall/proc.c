/** @file proc.c
 * 
 * @brief Implementation of `process' syscalls
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-12
 */

#include <exports.h>
#include <bits/errno.h>
#include <config.h>
#include <kernel.h>
#include <syscall.h>
#include <sched.h>

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>

int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
        /*
                -ESCHED: task not schedulable (part 2?)
        init mutexes, run UB test (????), sort tasks (part 2?)
        set up tasks/schedule them
        */
	uint8_t pri[num_tasks];
	size_t i;

	// make sure we're not allocating too many tasks
	if(num_tasks > OS_MAX_TASKS - 1)
		return EINVAL;
	// no tasks outside valid address range
	if(!valid_addr(&tasks, sizeof(task_t) * num_tasks, USR_START_ADDR, USR_END_ADDR))
		return EFAULT;
	//no two tasks have the same priority
	for (i = 0; i < num_tasks; i++){
		for (j = 0; j < i; j++){
			if(pri[j] == tasks[i].cur_prio)
				return EINVAL;
		}
		pri[i] = tasks[i].cur_prio;
	}
	allocate_tasks(&tasks, num_tasks);
	// won't make it here:
	return -1;
}

int event_wait(unsigned int dev  __attribute__((unused)))
{
  return 1; /* remove this line after adding your code */	
}

/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num  __attribute__((unused)))
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);

	disable_interrupts();
	while(1);
}
