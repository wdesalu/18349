#include "load_user_prog.h"

void exit(int status){                                         
	//calls assembly  
	exit_to_kernel();
	return;                                          
}
