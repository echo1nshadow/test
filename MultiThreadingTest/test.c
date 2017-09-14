#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>

pthread_mutex_t mux;
pthread_t thread_1;
pthread_t thread_2;
int i = 0;
void * thread()
{
	for( ; i < 99 ; )
	{
		usleep(50000);
		printf("thread1: %2d\n",i);
		pthread_mutex_lock(&mux);
			++i;
		pthread_mutex_unlock(&mux);
	}
	pthread_exit(NULL);
}

void * thread2()
{
	for( ; i < 99 ; )
	{
		usleep(50000);
		printf("thread2: %2d\n",i);
		pthread_mutex_lock(&mux);
			++i;
		pthread_mutex_unlock(&mux);
	}
	pthread_exit(NULL);
}
	
void thread_create()
{
	int temp;
	memset(&thread_1 , 0 , sizeof(thread));
	if((temp = pthread_create(&thread_1 , NULL ,thread , NULL)) != 0)
		printf("fail");
	else
		printf("success");
	memset(&thread_2 , 0 , sizeof(thread));
	if((temp = pthread_create(&thread_2, NULL, thread2 , NULL))!=0)
		printf("thread2 failed\n");
	else
		printf("thread2 created successfully\n");
}

void thread_wait()
{
	if(thread_1 != 0)
	{
		pthread_join(thread_1, NULL);
		printf("thread end\n");
	}
	if(thread_2 != 0)
	{
		pthread_join(thread_2 ,NULL);
		printf("thread2 end\n");
	}
}

int main()
{
	thread_create();
	thread_wait();
}
