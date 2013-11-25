/**
 * @file mutex.c
 *
 * @brief Implements mutices.
 *
 * @authors adesalu kafisher lrbloch
 *
 * 
 * @date 11/2013
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
  //Disable interrupts
  disable_interrupts();

  //loop thru all the mutexes and set their default vals
      
  int index;
        for (index = 0; index < OS_NUM_MUTEX; index++){
                gtMutex[index].bAvailable = TRUE;
                gtMutex[index].pHolding_Tcb = 0;
                gtMutex[index].bLock = FALSE;
                gtMutex[index].pSleep_queue = 0;
        }

	//Re-enable interrupts
	enable_interrupts();
	
}

int mutex_create(void)
{
  //Contacts
  int index;

  //Disable interrupts
  disable_interrupts();

  //Loop through all the mutexes and set to 1;
  for(index=0; index<OS_NUM_MUTEX; index++){
    //Check if available (0=yes,1=no)
    if(gtMutex[index].bAvailable == 0)
      gtMutex[index].bAvailable = 1;

    //Return index of available mutex
    return index;
  }

  //Enable Interrupts
  enable_interrupts();

  //No mutexes available, return error
  return EPERM;
}

int mutex_lock(int mutex  __attribute__((unused)))
{ 
  // Get the current task
  tcb_t* cur_tcb = get_cur_tcb();
  mutex_t* cur_mutex = &(gtMutex[mutex]);
 
  // Check if mutex is in range
  if((mutex <0) || (mutex >= OS_NUM_MUTEX)) return EINVAL;

  // Check if deadlock error
  if(cur_tcb == gtMutex[mutex].pHolding_Tcb) return EDEADLOCK;

  // Disable interrupts
  disable_interrupts();

  // If mutex is locked (blocked), wait until freed up by sleeping
  while(cur_mutex->bLock == 1){
    // Enable interrupts
    enable_interrupts();
    
    dispatch_sleep();
    
    //Disable interrupts
    disable_interrupts();
  }
  
  // Set holding Tcb to current task, set bLock = TRUE, give curr\ent task highest priority, set cur tasks's "holds_lock" val to 1
  cur_mutex->bLock = 1;
    cur_mutex->pHolding_Tcb = cur_tcb;
    cur_tcb->cur_prio = highest_prio();
    cur_tcb->holds_lock = 1;

    // Enable Interrupts
    enable_interrupts();

    return 0;
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
	
  // Get current task & mutex 
  //tcb_t* cur_tcb = get_cur_tcb();
  mutex_t* cur_mutex = &(gtMutex[mutex]);

  // Disable interrupts
  disable_interrupts();

  // Make sure mutex param is valid (if not, return -EINVAL)
  if((mutex <0) || (mutex >= OS_NUM_MUTEX) || (cur_mutex->bLock != 1)) return EINVAL;


  //current task doesn't hold mutex, enable interrupts (return -EPERM)
  //v. else:
  //                get sleep task pointer from mutex
  //            add tasks from mutex's sleep queue to the run queue
  //            reset mutex to be unlocked (hodling tcb = 0, bLock = false, sleep_queue = 0)
                
  //            loop through mutexes, if none are holding the current task, then set
  //            the current task's holds_lock to 0, and cur_prio to its native prio

  cur_mutex->bLock = 0;
  cur_mutex->pHolding_Tcb = 0;
   	  
  //enable interrupts
  enable_interrupts();
	
  return 1; // fix this to return the correct value
}

