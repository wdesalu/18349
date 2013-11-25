/**
 * @file device.c
 *
 * @brief Implements simulated devices.
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-12-01
 */

#include <types.h>
#include <assert.h>

#include <task.h>
#include <sched.h>
#include <device.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>

/**
 * @brief Fake device maintainence structure.
 * Since our tasks are periodic, we can represent 
 * tasks with logical devices. 
 * These logical devices should be signalled periodically 
 * so that you can instantiate a new job every time period.
 * Devices are signaled by calling dev_update 
 * on every timer interrupt. In dev_update check if it is 
 * time to create a tasks new job. If so, make the task runnable.
 * There is a wait queue for every device which contains the tcbs of
 * all tasks waiting on the device event to occur.
 */

struct dev
{
  tcb_t* sleep_queue;
  
  //Does not overflow, and used to match when device tasks are run
  unsigned long   next_match;
};
typedef struct dev dev_t;

/* devices will be periodically signaled at the following frequencies */
const unsigned long dev_freq[NUM_DEVICES] = {100, 200, 500, 50};
static dev_t devices[NUM_DEVICES];

/**
 * @brief Initialize the sleep queues and match values for all devices.
 */
void dev_init(void)
{
   /* the following line is to get rid of the warning and should not be needed */	
   //devices[0]=devices[0];
  
  //Constants
  uint8_t index;
  
  //Initialize each device independently
  for(index = 0; index < NUM_DEVICES; i++){
    //set initialized frequencies
    devices[index].next_match = dev_freq[index];
    
    //set sleep queues to 0
    devices[index].sleep_queue = 0;
  }
}


/**
 * @brief Puts a task to sleep on the sleep queue until the next
 * event is signalled for the device.
 *
 * @param dev  Device number.
 */
void dev_wait(unsigned int dev __attribute__((unused)))
{
  unsigned int index = dev;
  
  //Get currenttask
  tcb_t* cur_tcb = get_cur_tcb;
  
  //Add to front of sleep queue
  tcb_t* temp = dev.sleep_queue;
  cur_tcb->sleep_queue = temp;
  devices[index].sleep_queue = cur_tcb
  
  //Run sleep & go to next task
  dispatch_sleep();
}


/**
 * @brief Signals the occurrence of an event on all applicable devices. 
 * This function should be called on timer interrupts to determine that 
 * the interrupt corresponds to the event frequency of a device. If the 
 * interrupt corresponded to the interrupt frequency of a device, this 
 * function should ensure that the task is made ready to run 
 */
void dev_update(unsigned long millis __attribute__((unused)))
{
  //Constants
  uint8_t index;
  tcb_t* task;

  //Device Update
  //Check each device independently
  for(index = 0; i < NUM_DEVICES; i++){
    //Check if millis matches a device next_match
    if(millis == devices[index].next_match){
      
      for(task = devices[index].sleep_queue; lIndex != NULL; task = task->sleep_queue){
	//Remove from task sleepqueue
	task->sleep_queue = 0;

	//Add to runqueue
	runqueue_add(task, task->cur_prio);
      }

      //Remove from device sleepqueue
      devices[index].sleep_queue = 0;
      
      //Update next_match
      devices[index].next_match = devices[index].next_match + millis;
    }
  }

  //Start running task
  dispatch_save();
}

