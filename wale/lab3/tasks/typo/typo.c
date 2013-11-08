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
  //  return 0;

  while(1) {
    printf("Enter string:\n");
    char buf[1024];
   
    //Get Start Time
    unsigned int start_time = time();
    printf("Start Time: %x\n", start_time);

    // Read Input String into buffer
    size_t len = read(0, buf, 1024);
    printf("String Length: %x\n", (unsigned int)len);

    //Get End Time
    unsigned int end_time = time();
    printf("End Time: %x\n", start_time);

    return 0;

    write(1, buf, len);
    printf("time: %d", (int)(end_time - start_time)/1000);
    printf(".%d\n", (int)(end_time = start_time)%1000);
  }
  printf("Ending Typo function \n");
  return 0;
}
