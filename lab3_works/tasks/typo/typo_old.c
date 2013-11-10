/** @file typo.c
 *
 * @brief Echos characters back with timing data.
 *
 * Links to libc.
 */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  printf("Starting Typo function \n");
  //printf("current time: %lu\n", time());
  //  return 0;
  int len;
  
  while(1) {
    write(STDOUT_FILENO, "Enter string:\n", 100);
    char buf[1024];
   
    //Get Start Time
    
   /* unsigned int start_time = time();
    printf("Start Time: %x\n", start_time);
*/
    // Read Input String into buffer
    len = read(STDIN_FILENO, buf, sizeof(buf));
    printf("String Length: %x\n", (int)len);
/*
    //Get End Time
    unsigned int end_time = time();
    printf("End Time: %x\n", start_time);
*/
    //return 0;

    write(STDOUT_FILENO, buf, len);
  /*  printf("time: %d", (int)(end_time - start_time)/1000);
    printf(".%d\n", (int)(end_time = start_time)%1000);
    */
  }
  printf("Ending Typo function \n");
  return 0;
}
