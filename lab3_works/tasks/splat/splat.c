/** @file splat.c
 *
 * @adesalu, kafisher, lrbloch
 *
 * Links to libc.
 */
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "bits/fileno.h"
#include <stdio.h>

void main(int argc, char** argv)
{
	char out1[3]="\b|";
	char out2[3]="\b/";
	char out3[3]="\b-";
	char out4[3]="\b\\";
	while(1){
		write(STDOUT_FILENO, out1, sizeof(out1));
		sleep(200);
                write(STDOUT_FILENO, out2, sizeof(out2));
                sleep(200);
                write(STDOUT_FILENO, out3, sizeof(out3));
                sleep(200);
                write(STDOUT_FILENO, out4, sizeof(out4));
                sleep(200);
	}
}
