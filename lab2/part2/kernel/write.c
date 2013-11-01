#include "include/bits/errno.h"
#include "include/bits/swi.h"
#include "include/bits/fileno.h"
#include <exports.h>

ssize_t write(int fd, const void* buf, size_t count){                           
  int i;
  char* buffer = (char*) buf;
                                                                              
  int SDRAM_start = 0xa0000000;                                                 
  int SDRAM_end = 0xa3ffffff;                                                    
  int SDRAM_size = SDRAM_end-SDRAM_start;                                       
                                                                               
  //Case 1: If doesnt match stdout                                              
  if (fd != STDOUT_FILENO) return EBADF; //in errno.h = 9                       
                                                                              
  //Case 2: mem range & size outside range of SDRAM                           
  if((count > SDRAM_size) || (buf < (void*)SDRAM_start) || (buf > (void*)SDRAM_end))
   return EFAULT; //in errno.h = 14                                          
  
  //Case 3: write buffer to stdout                                              
  for (i = 0; i < count ; i++){
    putc(buffer[i]);                                                               
  }                                                                             
  return count;                                                                 
}
