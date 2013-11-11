/** @file date.c
 *
 * @Authors: Sara Roy <slroy@andrew.cmu.edu>
 *          Samantha Klonaris <sklonari@andrew.cmu.edu>
 *  	    Derek Miller <damiller@andrew.cmu.edu>
 * @Date: 11/4/20 
 */




/* To run this program the user needs to enter a current 
* date and time in the format "month day year hour minute" 
* as all ints.
* example: 11 7 2012 20 15
* this will print "Novemeber 7, 2012 10:15"
* the time and date will update as long as the program is 
* running and will print the updated values
* every minute.
*/




#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//number days in each corresponding month
const int numDaysMonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const char* months[13]={" ","January", "February", "March", "April", "May", "June", "July","August", "September", "October", "November", "December"};


//prints the current date in correct formats
void date(int month, int day, int year, int hour, int minute){
	printf("Today is %s %d, %d\n", months[month], day, year);
	if (hour > 13)
		hour -= 12;
	if(minute < 10)
		printf("The time is %d:0%d\n", hour, (int)minute);
	else	
		printf("The time is %d:%d\n", hour, (int)minute);
}

int main(int argc, char** argv){
	
	int month = atoi(argv[1]);
	int day = atoi(argv[2]);
	int year = atoi(argv[3]);
	int hour = atoi(argv[4]);
	int minute = atoi(argv[5]);
	//Set the offset to current running times
	// print the current date and time
	date(month, day, year, hour, minute);
	while(1){
		sleep(60000);
		minute ++;
		// increase hour
		if(minute >= 60){
			minute -= 60;
			hour ++;
			// increase day
			if(hour > 24){
				hour -= 24;
				day ++;
				// increase month
				if(day > numDaysMonth[month]){
					day = 1;
					month ++;
					//increase year
					if(month > 12){
						month = 1;
						year ++;
					}
				}
			}
			
		}
		// print out new day and time
		date(month, day, year, hour, minute);
	}
}


