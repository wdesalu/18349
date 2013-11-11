#include "include/bits/errno.h"
#include "include/bits/swi.h"
#include "include/bits/fileno.h"
#include <exports.h>
#include <globals.h>

ssize_t write(int fd, const void* buf, size_t c){                           
  int i;
  int count = (int) c;
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
