#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void){
	printf(1, "Among all active processes in the system maximum PID is %d\n", getMaxPID());
	exit();
}