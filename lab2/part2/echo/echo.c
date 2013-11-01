/** @file: echo.c
 *
 * @author  Laura Bloch (lrbloch@andrew.cmu.edu)
 *	    Kylie Fisher (kafisher@andrew.cmu.edu)
 *	    Wale Desalu (adesalu@andrew.cmu.edu)
 *
 * @date    10/27/2013 11:30:00
 */

//Imported Libraries
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define BUF_SIZE 1024

int main(void) {
        int streamLen, outLen;
        char string[100];
        while(1)
        {
	 	streamLen = read(STDIN_FILENO, string, BUF_SIZE);
               
		//Check if length > 0
		if(streamLen == 0) exit(0);
                if(streamLen < 0) exit(1);

		outLen = write(STDOUT_FILENO, string, streamLen * sizeof(char));
                
		//Check if outlen > 0
		if(outLen < 0)
                        exit(1);
                while(outLen < streamLen)
                       outLen += write(STDOUT_FILENO, &string[outLen - 1], (streamLen - outLen) * sizeof(char));
        }

	return 1;
}
