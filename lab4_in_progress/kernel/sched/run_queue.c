/** @file run_queue.c
 * 
 * @brief Run queue maintainence routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-21
 */

#include <types.h>
#include <assert.h>

#include <kernel.h>
#include <sched.h>
#include "sched_i.h"



static tcb_t* run_list[OS_MAX_TASKS]  __attribute__((unused));

/* A high bit in this bitmap means that the task whose priority is
 * equal to the bit number of the high bit is runnable.
 */
static uint8_t run_bits[OS_MAX_TASKS/8] __attribute__((unused));

/* This is a trie structure.  Tasks are grouped in groups of 8.  If any task
 * in a particular group is runnable, the corresponding group flag is set.
 * Since we can only have 64 possible tasks, a single byte can represent the
 * run bits of all 8 groups.
 */
static uint8_t group_run_bits __attribute__((unused));

/* This unmap table finds the bit position of the lowest bit in a given byte
 * Useful for doing reverse lookup.
 */
static uint8_t prio_unmap_table[]  __attribute__((unused)) =
{

0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

/**
 * @brief Clears the run-queues and sets them all to empty.
 */
void runqueue_init(void)
{
	int i;
    	for (i = 0; i < OS_MAX_TASKS; i++){
        	run_list[i] = 0;
    	}
    	for (i = 0; i < OS_MAX_TASKS/8; i++){
        	run_bits[i] = 0;
    	}
    	group_run_bits = 0; 
}

/**
 * @brief Adds the thread identified by the given TCB to the runqueue at
 * a given priority.
 *
 * The native priority of the thread need not be the specified priority.  The
 * only requirement is that the run queue for that priority is empty.  This
 * function needs to be externally synchronized.
 */
void runqueue_add(tcb_t* tcb  __attribute__((unused)), uint8_t prio  __attribute__((unused)))
{
	uint8_t ostcby;
	uint8_t ostcbx;

	// make sure the priority is possible
	if(prio >= OS_MAX_TASKS) return;
	// if that priority isn't taken, set it to tcb
	if(run_list[prio] == 0){
		run_list[prio] = tcb;
	}

	ostcby = prio >> 3;
	ostcbx = (prio & 0x07);
	// set bit ostcby of group_run_bits to 1
	group_run_bits = group_run_bits | (0x1 << ostcby);
	// set bit ostcbx of run_bits[ostcby] to 1
	run_bits[ostcby] = run_bits[ostcby] | (0x1 << ostcbx);
}


/**
 * @brief Empty the run queue of the given priority.
 *
 * @return  The tcb at enqueued at the given priority.
 *
 * This function needs to be externally synchronized.
 */
tcb_t* runqueue_remove(uint8_t prio  __attribute__((unused)))
{
	uint8_t ostcby;
	uint8_t ostcbx;

	tcb_t* ret_val;
	if(prio < OS_MAX_TASKS && run_list[prio] != 0){
		ret_val = run_list[prio];
		run_list[prio] = 0;
	}
	else if (prio > OS_MAX_TASKS) ret_val = EINVAL;
	else ret_val = ESRCH;

	ostcby = prio >> 3;
        ostcbx = (prio & 0x07);

        // set bit ostcbx of run_bits[ostcby] to 0
        run_bits[ostcby] = run_bits[ostcby] & ~(0x1 << ostcbx);
	/* 
	   if the run_bits for that group are all empty,
	   set bit ostcby of group_run_bits to 0 
	*/
	if(run_bits[ostcby] == 0)
        	group_run_bits = group_run_bits & ~(0x1 << ostcby);
	
	return ret_val;
}

/**
 * @brief This function examines the run bits and the run queue and returns the
 * priority of the runnable task with the highest priority (lower number).
 */
uint8_t highest_prio(void)
{
	int i = prio_unmap_table[group_run_bits];
    	return (i << 3) + prio_unmap_table[run_bits[i]];
}
