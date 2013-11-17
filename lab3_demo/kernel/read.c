#include <bits/errno.h>
#include <bits/swi.h>
#include <bits/fileno.h>
#include <exports.h>
#include <globals.h>

ssize_t read(int fd, void* buf, size_t c){                                  

  char *buffer = (char*) buf;
  int i = 0;
  char newChar;
  int count = (int) c;
                                                                              
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
