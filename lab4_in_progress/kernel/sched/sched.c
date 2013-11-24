/** @file sched.c
 * 
 * @brief Top level implementation of the scheduler.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

#include <types.h>
#include <assert.h>

#include <kernel.h>
#include <config.h>
#include "sched_i.h"

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>

tcb_t system_tcb[OS_MAX_TASKS]; /*allocate memory for system TCBs */

void sched_init(task_t* main_task  __attribute__((unused)))
{
	
}

/**
 * @brief This is the idle task that the system runs when no other task is runnable
 */
 
static void __attribute__((unused)) idle(void)
{
	 enable_interrupts();
	 while(1);
}

/**
 * @brief Allocate user-stacks and initializes the kernel contexts of the
 * given threads.
 *
 * This function assumes that:
 * - num_tasks < number of tasks allowed on the system.
 * - the tasks have already been deemed schedulable and have been appropriately
 *   scheduled.  In particular, this means that the task list is sorted in order
 *   of priority -- higher priority tasks come first.
 *
 * @param tasks  A list of scheduled task descriptors.
 * @param size   The number of tasks is the list.
 */
void allocate_tasks(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
	/*
		set up tcbs for all tasks
		put task in runqueue (make it avail for running)
		set up tcb for idle task
		make idle task schedulable
	*/
	size_t i;
	//set up tcb for idle task
        system_tcb[IDLE_PRI0].native_prio = IDLE_PRI0;
        system_tcb[IDLE_PRI0].cur_prio = IDLE_PRI0;
	//system_tcb[0].sched_context_t.	
	// new tasks don't hold locks or have initialized sleepqueues
	system_tcb[IDLE_PRI0].holds_lock = 0;
	system_tcb[IDLE_PRI0].sleep_queue = 0;
	runqueue_init();
	runqueue_add(&system_tcb[i], i);
	
	for(i = 0; i < num_tasks; i++){
		//don't use pri 0: that's for mutii
		system_tcb[i].native_prio = i+1;
		system_tcb[i].cur_prio = i+1;
		//system_tcb[i].sched_context_t.
		//add task to runqueue
		//system_tcb[0].sched_context_t.        
	        // new tasks don't hold locks or have initialized sleepqueues
        	system_tcb[i].holds_lock = 0;
       	 	system_tcb[i].sleep_queue = 0;

		runqueue_add(&system_tcb[i+1], i+1);
	}
	
	//schedule idle task
	dispatch_init(&system_tcb[IDLE_PRI0]);
	
}

