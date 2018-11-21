#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <stdint.h>
#include <sched.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

inline int set_cpu(int i){
	cpu_set_t mask;
	CPU_ZERO(&mask);

	CPU_SET(i,&mask);

	printf("thread %u, i = %d\n",pthread_self(),i);
	if(-1 == pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask))
		return -1;
	return 0;
}

void *fun(void *i)
{
	int _i = *(int *)i;
	if(set_cpu(_i))
		printf("set cpu error\n");
	unsigned long a = 0;
	while(1){
		a += rand();
	}
	return NULL;
}

int main()
{
	int i = 0;
	int cpu_nums = sysconf(_SC_NPROCESSORS_CONF);
	printf("cpu_numbers : %d\n",cpu_nums);
	
	pthread_t Thread[10];
	int tmp[10];
	for(i = 0; i < 10;++i){
		tmp[i]= i;
		pthread_create(&Thread[i],NULL,fun,&tmp[i]);
	}

	for(i = 0; i < 10;++i){
		pthread_join(Thread[i],NULL);
	}

	return 0;
}
