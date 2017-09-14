#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#define SIZE 40

pthread_t work;
pthread_t monitor;



void display();
void init();
void run();
void turnleft();
void turnright();
void go();

unsigned long count = 0;
int i = 0 ;
int j = 0 ;
int direction = 0;			//0:上  1:左  2:下  3:右
int pad[SIZE][SIZE*3] = {0};
FILE *fp = NULL;



void * thread1()
{
/*
	if(fp=(fopen("/home/echo/data/langtonsant.log","a+"))==NULL)
	{
		printf("文件不能正常打开\n");
		exit(1);
	}
*/
	init();
	while(1)
	{
		
		display();
		run();
		usleep(40000);
	}
}

void * thread2()
{
	fp = fopen("langtonsant.log","a+");
	printf("进入线程2\n");
/*
	for( ; i < 99 ; )
	{
		usleep(50000);
		pthread_mutex_lock(&mux);
		printf("thread2: %2d\n",i);
			++i;
		pthread_mutex_unlock(&mux);
	}
*/
	while(getchar() == 'q')
		pthread_kill(work,2);
	
	fclose(fp);
	pthread_exit(NULL);
}

void create()
{
	int temp;
	memset(&work, 0 , sizeof(work));
	if((temp = pthread_create(&work, NULL ,thread1 , NULL)) != 0)
		printf("thread1 created failed\n");
	else
		printf("thread1 created successfully\n");
	memset(&monitor, 0 , sizeof(monitor));
	if((temp = pthread_create(&monitor, NULL, thread2 , NULL))!=0)
		printf("thread2 created failed\n");
	else
		printf("thread2 created successfully\n");
}

void thread_wait()
{
	if(work!= 0)
	{
		pthread_join(work, NULL);
		printf("work thread ended\n");
	}
	if(monitor!= 0)
	{
		pthread_join(monitor,NULL);
		printf("monitor thread ended\n");
	}
}

void display()
{
	count++;
	system("clear");
	int a = 0 ; 
	int b = 0;
	for( a = 0 ; a < SIZE ; a++)
	{
		printf("%-2d",a);
		for( b = 0 ; b < SIZE * 3; b++)
		{
			if(pad[a][b] == 1)
			printf("*");
			else
			printf("-");
		}
		printf("\n");
	}
	printf("%ld		i=%d	j=%d	status:%d	direction:%d\n",count,i,j,pad[i][j],direction);	
	fprintf(fp,"%ld		i=%d	j=%d	status:%d	direction:%d\n",count,i,j,pad[i][j],direction);	
}

		
void init()
{
	int a = SIZE / 2;
	int b = SIZE / 2 * 3;
	pad[a][b] = 1;
	i = a;
	j = b;
}
void run()
{
	if(pad[i][j] == 0)
	{
		turnleft();
		go();
	}
	if(pad[i][j] == 1)
	{
		turnright();
		go();
	}
}
void turnleft()
{
	if(direction == 0)
	{
		direction = 1;
		return ;
	}
	if(direction == 1)
	{
		direction = 2;
		return ;
	}
	if(direction == 2)
	{
		direction = 3;
		return ;
	}
	if(direction == 3)
	{
		direction = 0;
		return ;
	}
}
void turnright()
{
	if(direction == 0)
	{
		direction = 3;
		return ;
	}
	if(direction == 1)
	{
		direction = 0;
		return ;
	}
	if(direction == 2)
	{
		direction = 1;
		return ;
	}
	if(direction == 3)
	{
		direction = 2;
		return ;
	}
}
void go()
{
	int x = 0;
	int y = 0;
	int temp1 , temp2;
	temp1 = i ;
	temp2 = j;
	if(direction == 0)
	{
		x = i-1;
		y = j;
	}
	if(direction == 1)
	{
		x = i;
		y = j-1;
	}
	if(direction == 2)
	{
		x = i+1;
		y = j;
	}
	if(direction == 3)
	{
		x = i;
		y = j+1;
	}
	if(pad[i][j] == 0)
	{
		pad[i][j] = 1;
	}
	else
	{
		pad[i][j] = 0;
	}
	i = x;
	j = y;
	if(i < 0)
	{
		i = temp1;
		direction = (direction+1) % 4;
	}
	if(j < 0)
	{
		j = temp2;
		direction = (direction+1) % 4;
	}
	if(i >= SIZE)
	{
		i = temp1;
		direction = (direction+1) % 4;
	}
	if(j >= SIZE*3)
	{
		j = temp2;
		direction = (direction+1) % 4;
	}
}

		
int main()
{
	create();
	wait();
	return 0;
}

	
