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
#include <lock.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>

int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
	size_t i, j;

	// make sure we're not allocating too many tasks, avoid 0 priority and 
	// idle task
	if(num_tasks > OS_MAX_TASKS - 2)
		return EINVAL;
	// no tasks outside valid address range
	if(!valid_addr(&tasks, sizeof(task_t) * num_tasks, USR_START_ADDR, USR_END_ADDR))
		return EFAULT;
	//check T, C of each task
	for (i = 0; i < num_tasks; i++){
		if(tasks[i].T < tasks[i].C || tasks[i].T == 0)
			return ESCHED;
	}

	// initialize mutices
	mutex_init();
	// sort tasks
	if(!assign_schedule(&tasks, num_tasks))
		return ESCHED;
	disable_interrupts();
	allocate_tasks(&tasks, num_tasks);
	dispatch_nosave();

	// won't make it here:
	return -1;
}

int event_wait(unsigned int dev  __attribute__((unused)))
{
	//get tcb of current task
	//check for mutex
	// check that dev is valid
	// disable interrupts
	//dev_wait
	// enable interrupts  
	return 0;
}

/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num  __attribute__((unused)))
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);

	disable_interrupts();
	while(1);
}
