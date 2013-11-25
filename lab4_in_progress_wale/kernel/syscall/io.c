/** @file io.c
 *
 * @brief Kernel I/O syscall implementations
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-16
 */

#include <types.h>
#include <bits/errno.h>
#include <bits/fileno.h>
#include <arm/physmem.h>
#include <syscall.h>
#include <exports.h>
#include <kernel.h>
#include <globals.h>

#define EOT_CHAR 0x04
#define DEL_CHAR 0x7f


/* Read count bytes (or less) from fd into the buffer buf. */
ssize_t read_syscall(int fd __attribute__((unused)), void *buf __attribute__((unused)), size_t count __attribute__((unused)))
{

  char *buffer = (char*) buf;
  size_t i = 0;
  char newChar;
  //int c = count;                                                                            
  //Case 1: If fd doesn't match stdin                       
  if(fd != STDIN_FILENO) return EBADF;                                          
                                                            
  if((count > SDRAM_SIZE) || (buf < (void*)SDRAM_START) || (buf > (void*)SDRAM_END))
     return EFAULT;                                                             
   
  //Case 3: read into buffer                                    
  for(i = 0; i < count; i++){                                                   
	newChar = getc();                                                           
    //EOT character                                                             
    if(newChar == 4){                                                       
      return i;                                                                 
    }                                                                           
                                                                                
    //Backspace or delete character                                             
    else if((newChar == '\b') || (newChar == 127)){                             
        if(i > 0) {                                                             
          puts("\b \b");                                                        
          i -= 2;                                                               
          buffer[i+1] = 0;                                                      
        }                                                                       
        else {                                                                  
          i -= 1;                                                               
        }                                                                       
    }                                                                           
                                                                                
    //Newline or Carriage return characters                                     
    else if((newChar == '\n') || (newChar =='\r')){                
     buffer[i] = '\n';                                                         
      putc('\n');                                                               
      return i;                                                                 
    }                                                                           
                                                                                
    //Regular characters                                                        
    else{                                                                       
      buffer[i] = newChar;                                                      
      putc(newChar);                                                            
    }                                                                           
  }                         
  return count;                                                                 
}                            

/* Write count bytes to fd from the buffer buf. */
ssize_t write_syscall(int fd  __attribute__((unused)), const void *buf  __attribute__((unused)), size_t count  __attribute__((unused)))
{

    size_t i;
//	int c = count;
  
  char* buffer = (char*) buf;
                                                                              
  //Case 1: If doesnt match stdout                                              
  if (fd != STDOUT_FILENO) return EBADF;                       
                                                                              
  //Case 2: mem range & size outside range of SDRAM                           
  if((count > SDRAM_SIZE) || (buf < (void*)SDRAM_START) || (buf > (void*)SDRAM_END))
   return EFAULT; //in errno.h = 14                                          
  
  //Case 3: write buffer to stdout                                              
  for (i = 0; i < count ; i++){
    putc(buffer[i]);                                                               
  }                                                                             
  return count;
	
}

