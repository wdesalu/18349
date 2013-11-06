/*
  adesalu
  kafisher
  lrbloch
  */

#include <stdio.h>
#include "math.h"

int main() {
	int x, y;
	char op;
	int check;
	int answer;

	while(1) 
	{
		// Reads the user's input and checks if there 
		// are the appropriate amount of arguments.	
		check = scanf("%d%c%d", &x, &op, &y);
		if(check != 3) 
			return 0;

		// This switch statement deals with the cases
		// for the different mathematical operators
		// and computes result as defined in math.c.
		switch(op) {
			case '+':  
				answer = add(x,y); 
				break;
			case '-':  
				answer = sub(x,y); 
				break;
			case '*':  
				answer = mul(x,y); 
				break;
			case '/':  
				answer = cdiv(x,y);
				break;
			case '%':  
				answer = mod(x,y); 
				break;
			default: 
				printf("Error. Invalid operator."); 
				return 0;
		}
		
		// Prints the answer and a new line.
		printf("%d\n\n", answer); 
	}
}

