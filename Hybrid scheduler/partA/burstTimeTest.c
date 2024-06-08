#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void){
	printf(1,"Burst time is set to 10\n");
	set_burst_time(10);
	printf(1, "Getting the value of burst time %d\n", get_burst_time());
	exit();
}