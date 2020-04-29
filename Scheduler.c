#define _GNU_SOURCE
#include "Scheduler.h"

void Unit_time(){
	 volatile unsigned long i; 
	 for(i=0;i<1000000UL;i++); 
}

int SET_CPU(int pid, int core){
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);
	if (sched_setaffinity(pid,sizeof(mask),&mask) < 0){
		fprintf(stderr, "sched_setaffinity() Failed\n");
		fprintf(stderr, "In Func %s: line #%d - \n",__PRETTY_FUNCTION__,__LINE__ );		
		exit(0);
	}
	return 0;
}

int Proc_Wake(int pid){
	struct sched_param param;
	param.sched_priority = 0;
	int retval = sched_setscheduler(pid,SCHED_OTHER,&param);
	if (retval < 0){
		fprintf(stderr, "[Proc_Wake] sched_setscheduler() Failed for %d\n",pid);
		return -1;
	}
	return retval;
}

int Proc_Block(int pid){
	struct sched_param param;
	param.sched_priority = 0;
	int retval  = sched_setscheduler(pid,SCHED_IDLE,&param);
	if (retval < 0){
		fprintf(stderr, "[Proc_Block] sched_setscheduler() Failed for %d\n",pid);
		return -1;
	}
	return retval;
}

int Proc_Exec(Process proc){

	int pid = fork();
	if (pid < 0){
		fprintf(stderr, "[Proc_Exec] fork() Failed\n");		
	}
	else if (pid == 0){
		long start = syscall(335);
		for (int i = 0; i < proc.execute; ++i){
			Unit_time();
		}
		long end = syscall(335);
		syscall(334,getpid(),start,end);
		exit(0);
	}
	SET_CPU(pid,1);
	return pid;
}

int Proc_next_FIFO(Process *Proc,int nProcess,int Run_idx){
	if (Run_idx != -1){
		return Run_idx;
	}

	int retval = -1;
	for (int i = 0; i < nProcess; ++i){
		if (Proc[i].pid == -1 || Proc[i].execute == 0){
			continue;
		}
		if (retval == -1 || Proc[i].ready < Proc[retval].ready){
			retval = i;
		}
	}
	return retval;
}
int Proc_next_RR(Process *Proc,int nProcess,int Run_idx,int cur_time,int last_time,Queue *q){
	int retval = -1;

	if (Run_idx == -1){
		for (int i = 0; i < nProcess; i++){
			if (q -> count == 0){
				if (Proc[i].pid != -1 && Proc[i].execute > 0){
					retval = i;
					break;
				}
			}
			else{
				retval = q -> front -> index;
			}
		}
	}
	else if ((cur_time - last_time) % 500 == 0){
	#ifdef debug
		printf("Schedule_queue: ");
			Node *ptr = q -> front;
			while( ptr!= NULL){
				printf("%d ",ptr->index);
				ptr = ptr -> next;
			}
			printf("\n");
		#endif
		if (q -> count == 1){
			retval = q -> front -> index;
		}
		else if (q -> count > 1){
			Node *temp;
			temp = q -> front;
			q -> front = temp -> next;
			temp -> next = NULL;
			q -> rear -> next = temp;
			q -> rear = temp;
			retval = q -> front -> index;
		}
	}
	else{
		retval = Run_idx;
	}
	return retval;
}
int Proc_next_SJF(Process *Proc,int nProcess,int Run_idx){
	if (Run_idx != -1){
		return Run_idx;
	}

	int retval = -1;

	for (int i = 0; i < nProcess; ++i){
		if (Proc[i].pid == -1 || Proc[i].execute == 0){
			continue;
		}
		if (retval == -1 || Proc[i].execute < Proc[retval].execute){
			retval = i;
		}
	}
	return retval;
}
int Proc_next_PSJF(Process *Proc,int nProcess,int Run_idx){
	int retval = -1;

	for (int i = 0; i < nProcess; ++i){
		if (Proc[i].pid == -1 || Proc[i].execute == 0){
			continue;
		}
		if (retval == -1 || Proc[i].execute < Proc[retval].execute){
			retval = i;
		}
	}
	return retval;
}

void init(Queue *q){
	q -> count = 0;
	q-> front = NULL;
	q -> rear = NULL;
}
void enqueue(Queue *q,int Run_idx){
	Node *current = (Node *)malloc(sizeof(Node));
	current -> index = Run_idx;
	current -> next = NULL;
	if (q -> count != 0){
		q -> rear -> next = current;
		q -> rear = current;
	}
	else{
		q -> front = q -> rear = current;
	}
	q -> count++;
}

int cmp(const void *a,const void *b){
	return (((Process*)a)->ready) - (((Process*)b)-> ready);
}

int cmp_execute(const void *a,const void *b){
	return (((Process*)a)->execute) - (((Process*)b)-> execute);
}
