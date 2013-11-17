/** @file sys_handler.c
 *
 * @Authors: Sara Roy <slroy@andrew.cmu.edu>
 *          Samantha Klonaris <sklonari@andrew.cmu.edu>
 *  	    Derek Miller <damiller@andrew.cmu.edu>
 * @Date: 11/4/20 
 */

#include <exports.h> 
#include <bits/swi.h> 
#include <bits/fileno.h> 
#include <bits/errno.h>

extern volatile long sys_time;
 
ssize_t read(int fd, void *buf, size_t count){ 
   	char c; 
	char* charBuf = (char*)buf;
    
   	// return error if file descriptor isn't stdin
   	if (fd != STDIN_FILENO) 
     		return -EBADF; 
    
	// return error if memory range of buffer is outside SDRAMss
   	if (((unsigned int) buf + count) > 0xa3ffffff || (unsigned int) (buf) < 0xa0000000) 
     		return -EFAULT;  
    	
	unsigned int i = 0; 
    	while(i != count){ 
		// get character
		c = getc(); 
		// return number of characters read after reaching EOT character
		if (c == 4){
	  		return (ssize_t) i; 
		}
		// account for backspace or delete
		else if ((c == 8 || c == 127) && i != 0){ 
			i--;
			puts("\b \b");
		} 
		// if newline or enter, return number of characters read and place new line
		else if (c==10 || c==13){ 
			putc(10); 
			charBuf[i] =10; 
			i++; 
			return (ssize_t) i; 
		}
		// otherwise echo character to stdout
		else{ 
			charBuf[i] = c; 
			putc(c); 
			i++; 
		} 
	} 
	// return number of characters read
	return (ssize_t) i; 
} 
 
ssize_t write(int fd, const void *buf, size_t count){
   	// return error if file descriptor isn't stdout
	if (fd != STDOUT_FILENO){ 
      		return -EBADF; 
   	} 

   	char* charBuf = (char*)buf;
	// return error if memory range of buffer is outside StrataFlash ROM or SDRAM
   	if (!(((unsigned int) buf + count) < 0xa3ffffff && (unsigned int)buf > 0xa0000000) &&
   	    !(((unsigned int) buf + count) < 0x00FFFFFF && (unsigned int)buf > 0x0))
     		return -EFAULT; 

   	size_t counter = 0;
	// write characters to stdout
   	while(counter<count){ 
      		putc(charBuf[counter]); 
      		counter++; 
  	} 
    
	// return number of characters written
	return count;
}  

long time(){
	// Return the running total system time in ms
	return sys_time;
}

void sleep(long time){
	// Calculate the time to end at
	long end = sys_time + time;
	
	// Loop until the system time surpasses the end time
	while(sys_time <= end);
}

 

