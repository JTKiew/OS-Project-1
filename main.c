#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	char schedule_policy[50];
	scanf("%s\n",schedule_policy);
	fflush(stdin);
	if (strcmp(schedule_policy, "FIFO") == 0) {
		execl("./FIFO", "./FIFO", (char *)0); 
	}
	else if (strcmp(schedule_policy, "RR") == 0) {
		execl("./RR", "./RR", (char *)0); 
	}
	else if (strcmp(schedule_policy, "SJF") == 0) {
		execl("./SJF", "./SJF", (char *)0); 
	}
	else if (strcmp(schedule_policy, "PSJF") == 0) {
		execl("./PSJF", "./PSJF", (char *)0);
	}
	else {
		fprintf(stderr, "Invalid policy: %s",(schedule_policy));
		exit(0);
	}
	return 0;
}