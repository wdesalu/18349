#include <exports.h> 
#include <bits/swi.h> 
#include <bits/fileno.h> 
#include <bits/errno.h>
/*
 * Authors: Sara Roy <slroy@andrew.cmu.edu>
 *          Samantha Klonaris <sklonari@andrew.cmu.edu>
 *  	    Derek Miller <damiller@andrew.cmu.edu>
 * Date: 10/7/20 
 */

 
ssize_t read(int fd, void *buf, size_t count){ 
	
   	char c; 
	char* charBuf = (char*)buf;
    
   	if (fd != STDIN_FILENO) 
     		return -EBADF; 
    
   	if (((unsigned int) buf + count) > 0xa3ffffff || (unsigned int) (buf) < 0xa0000000) 
     		return -EFAULT; 
    	
	unsigned int i = 0; 
    	while(i != count){ 
		c = getc(); 
		if (c == 4){
	  		return (ssize_t) i; 
		}
		else if ((c == 8 || c == 127) && i != 0){ 
			i--;
			puts("\b \b");
		} 
		else if (c==10 || c==13){ 
			putc(10); 
			charBuf[i] =10; 
			i++; 
			return (ssize_t) i; 
		}else{ 
			charBuf[i] = c; 
			putc(c); 
			i++; 
		} 
	} 
	return (ssize_t) i; 
} 
 
ssize_t write(int fd, const void *buf, size_t count){
   	if (fd != STDOUT_FILENO){ 
      		return -EBADF; 
   	} 

   	char* charBuf = (char*)buf;
   	if (!(((unsigned int) buf + count) < 0xa3ffffff && (unsigned int)buf > 0xa0000000) &&
   	    !(((unsigned int) buf + count) < 0x00FFFFFF && (unsigned int)buf > 0x0))
     		return -EFAULT; 

   	size_t counter = 0;
   	while(counter<count){ 
      		putc(charBuf[counter]); 
      		counter++; 
  	} 
    
	return counter; 
}  
 

