/**
 * @file mutex.c
 *
 * @brief Implements mutices.
 *
 * @author Harry Q Bovik < PUT YOUR NAMES HERE
 *
 * 
 * @date  
 */

//#define DEBUG_MUTEX

#include <lock.h>
#include <task.h>
#include <sched.h>
#include <bits/errno.h>
#include <arm/psr.h>
#include <arm/exception.h>
#ifdef DEBUG_MUTEX
#include <exports.h> // temp
#endif

mutex_t gtMutex[OS_NUM_MUTEX];

void mutex_init()
{
	//loop thru all the mutexes and set their default vals
	int i;
	for (i = 0; i < OS_NUM_MUTEX; i++){
		gtMutex[i].bAvailable = TRUE;
		gtMutex[i].pHolding_Tcb = 0;
		gtMutex[i].bLock = FALSE;
		gtMutex[i].pSleep_queue = 0;
	}	
}

int mutex_create(void)
{
	//return index of first available mutex
	return 1; // fix this to return the correct value
}

int mutex_lock(int mutex  __attribute__((unused)))
{
	// i. get the current task
	// ii. disable interrupts
	// iii. make sure mutex parameter is valid
	// iv. enable interrupts if a task locks the mutex (?)
	// v. if the mutex is free, set holding Tcb to current task, set bLock = TRUE, give current
		// task highest priority, set cur tasks's "holds_lock" val to 1
	// vi. if the mutex is already locked: wait for it to free up, then do v. but enable interrupts


	return 1; // fix this to return the correct value
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
/*
	i. get current task
	ii. disable interrupts
	iii. make sure mutex param is valid (if not, return -EINVAL)
	iv. if current task doesn't hold mutex, enable interrupts (return -EPERM)
	v. else:
		get sleep task pointer from mutex
		add tasks from mutex's sleep queue to the run queue
		reset mutex to be unlocked (hodling tcb = 0, bLock = false, sleep_queue = 0)
		
		loop through mutexes, if none are holding the current task, then set
		the current task's holds_lock to 0, and cur_prio to its native prio

		enable interrupts
*/
	return 1; // fix this to return the correct value
}

