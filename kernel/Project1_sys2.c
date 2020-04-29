#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage long sys_Project1_sys2(void){
	static const long BASE = 1000000000;
	struct timespec time;
	getnstimeofday(&time);
	return time.tv_sec*BASE + time.tv_nsec;
}
