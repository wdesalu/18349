#include <load_user_prog.h>

void exit(int status){                                         
  exit_to_kernel();
	return;                                          
}
