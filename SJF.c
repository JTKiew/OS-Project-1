#define _GNU_SOURCE
#include "Scheduler.h"

static int cur_time;
static int last_time;
static int Fin_Proc;
static int Run_idx;

//COMFIRMED 

int Proc_next(Process *Proc,int nProcess){
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

int main(int argc, char const *argv[]){
	int nProcess;
	scanf("%d\n",&nProcess);
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
			waitpid(Proc[Run_idx].pid,NULL,0);
			printf("%s %d\n",Proc[Run_idx].name,Proc[Run_idx].pid);
			fflush(stdout);
			Run_idx = -1;
			Fin_Proc++;
			if (Fin_Proc == nProcess){
				break;
			}
		}

		for (int i = 0; i < nProcess; ++i)
		{
			if (Proc[i].ready == cur_time){
				Proc[i].pid = Proc_Exec(Proc[i]);
				Proc_Block(Proc[i].pid);
			}
		}

		int next = Proc_next_SJF(Proc,nProcess,Run_idx);
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