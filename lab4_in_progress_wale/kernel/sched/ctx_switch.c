/** @file ctx_switch.c
 * 
 * @brief C wrappers around assembly context switch routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-21
 */
 

#include <types.h>
#include <assert.h>

#include <config.h>
#include <kernel.h>
#include "sched_i.h"

#ifdef DEBUG_MUTEX
#include <exports.h>
#endif

static __attribute__((unused)) tcb_t* cur_tcb; /* use this if needed */

/**
 * @brief Initialize the current TCB and priority.
 *
 * Set the initialization thread's priority to IDLE so that anything
 * will preempt it when dispatching the first task.
 */
void dispatch_init(tcb_t* idle __attribute__((unused)))
{
  cur_tcb = idle;
}


/**
 * @brief Context switch to the highest priority task while saving off the 
 * current task state.
 *
 * This function needs to be externally synchronized.
 * We could be switching from the idle task.  The priority searcher has been tuned
 * to return IDLE_PRIO for a completely empty run_queue case.
 */
void dispatch_save(void)
{
  uint8_t prio = highest_prio();

  tcb_t* old_tcb = cur_tcb;
  //cur ctx = removed from the front of the run queue                                       
  sched_context_t* cur_ctx = &(runqueue_remove(prio)->context);

  //old ctx = added to the run queue  
  sched_context_t* old_ctx = &(old_tcb->context);

  runqueue_add(old_tcb,old_tcb->cur_prio);

  //call a context switch
  ctx_switch_full(cur_ctx,old_ctx);
}

/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * don't save the current task state.
 *
 * There is always an idle task to switch to.
 */
void dispatch_nosave(void)
{
	/*
		context switch to the highest priority task without worrying about saving current task's context ("half switch")
	*/
  uint8_t prio = highest_prio();

  //cur ctx = removed from the front of the run queue    
  sched_context_t* cur_ctx = &(runqueue_remove(prio)->context);

  //call a context switch
  ctx_switch_half(cur_ctx);
}


/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * and save the current task but don't mark is runnable.
 *
 * There is always an idle task to switch to.
 */
void dispatch_sleep(void)
{
  uint8_t prio = highest_prio();

  //cur ctx = removed from the front of the run queue                                         
  sched_context_t* cur_ctx = &(runqueue_remove(prio)->context);

  //old ctx = added to the run queue                                                          
  sched_context_t* old_ctx = &(cur_tcb->context);

  //call a context switch                                                                     
  ctx_switch_full(cur_ctx,old_ctx);

}

/**
 * @brief Returns the priority value of the current task.
 */
uint8_t get_cur_prio(void)
{
  return cur_tcb->cur_prio;
}

/**
 * @brief Returns the TCB of the current task.
 */
tcb_t* get_cur_tcb(void)
{
  return cur_tcb;
}
