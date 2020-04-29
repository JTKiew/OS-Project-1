#define _GNU_SOURCE
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sched.h>

//Set up
struct process{
	char name[50];
	int ready;
	int execute;
	pid_t pid;
	bool done;
};
typedef struct process Process;
void Unit_time();
int SET_CPU(int pid,int core);
//Queue
struct node{
	int index;
	struct node * next;
};
typedef struct node Node;
struct queue{
	int count;
	Node *front;
	Node *rear;
};
typedef struct queue Queue;
void init(Queue *q);
void enqueue(Queue *q,int Run_idx);
//Process
int Proc_Wake(int pid);
int Proc_Block(int pid);
int Proc_Exec(Process Proc);
int Proc_next_FIFO(Process *Proc,int nProcess,int Run_idx);
int Proc_next_RR(Process *Proc,int nProcess,int Run_idx,int cur_time,int last_time,Queue *q);
int Proc_next_SJF(Process *Proc,int nProcess,int Run_idx);
int Proc_next_PSJF(Process *Proc,int nProcess,int Run_idx);
//Quick sort
int cmp(const void *a,const void *b);
int cmp_execute(const void *a,const void *b);

