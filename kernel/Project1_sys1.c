#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage void sys_Project1_sys1(int pid,long start,long end){
	static const long BASE = 1000000000;
	printk(KERN_INFO "[Project 1] %d %ld.%09ld %ld.%09ld\n",pid,start/BASE,start%BASE,end/BASE,end%BASE);
}
