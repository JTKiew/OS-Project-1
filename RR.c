#define _GNU_SOURCE
#include "Scheduler.h"

static int cur_time;
static int last_time;
static int Fin_Proc;
static int Run_idx;

int Proc_next(Process *Proc,int nProcess){
	int retval = -1;
	if (Run_idx == -1){
		for (int i = 0; i < nProcess; i++){
			if (Proc[i].pid != -1 && Proc[i].execute > 0){
				retval = i;
				break;
			}
		}
	}
	else if ((cur_time - last_time) % 500 == 0){
		retval = (Run_idx+1) % nProcess;
		while(Proc[retval].pid == -1 || Proc[retval].execute == 0){
			retval = (retval+1)%nProcess;
		}
	}
	else{
		retval = Run_idx;
	}
	return retval;
}

int main(int argc, char const *argv[]){
	int nProcess;
	scanf("%d\n",&nProcess);
	
	Queue *q = malloc(sizeof(Queue));
	init(q);

	Process *Proc = (Process*)malloc(nProcess*sizeof(Process));
	for (int i = 0; i < nProcess; ++i){
		scanf("%s%d%d\n",Proc[i].name,&Proc[i].ready,&Proc[i].execute);
		Proc[i].pid = -1;
	}
	qsort(Proc,nProcess,sizeof(Process),cmp);
	SET_CPU(getpid(),0);
	Proc_Wake(getpid());
	cur_time = 0;
	Run_idx = -1;
	Fin_Proc = 0;
	while(1){
		if (Run_idx != -1 && Proc[Run_idx].execute == 0){
		#ifdef debug	
			printf("Pre_queue: ");
			Node *ptr = q -> front;
			while( ptr!= NULL){
				printf("%d ",ptr->index);
				ptr = ptr -> next;
			}
			printf("\n");
		#endif
			q -> front = q -> front -> next;
			q -> count--;
		#ifdef debug
			printf("Cur_queue: ");
			ptr = q -> front;
			while( ptr!= NULL){
				printf("%d ",ptr->index);
				ptr = ptr -> next;
			}
			printf("\n");
		#endif
			waitpid(Proc[Run_idx].pid,NULL,0);
			printf("%s %d\n",Proc[Run_idx].name,Proc[Run_idx].pid);
			fflush(stdout);
			Run_idx = -1;
			Fin_Proc++;
			if (Fin_Proc == nProcess){
				break;
			}
		}

		for (int i = 0; i < nProcess; ++i){
			if (Proc[i].ready == cur_time){
				enqueue(q,i);
				Proc[i].pid = Proc_Exec(Proc[i]);
				Proc_Block(Proc[i].pid);
			}
		}
		#ifdef debug
		if ((cur_time - last_time)%500 == 0){
			printf("cur_time: %d Run_idx: %d\n",cur_time,Run_idx+1 );
		}
		#endif
		int next = Proc_next_RR(Proc,nProcess,Run_idx,cur_time,last_time,q);
		if (next != -1){
			if (Run_idx != next){
				Proc_Wake(Proc[next].pid);
				if (Run_idx != -1){
					Proc_Block(Proc[Run_idx].pid);
				}
				Run_idx = next;
				last_time = cur_time;
			}
		}

		Unit_time();

		if (Run_idx != -1){
			Proc[Run_idx].execute--;
		}
		cur_time++;
	}
	return 0;
}
