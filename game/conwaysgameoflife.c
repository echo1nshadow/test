#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define NUMBER 1600
#define number 40


void display();
void init();
void run();
int gamepad[number][number] = {0};


int main()
{
	init();
	while(1)
	{
		system("clear");
		display();
		sleep(1);
		run();
	}
	
	return 0;
}

void display()
{
	int i , j , c;
	c = 0;
	for( int a = 0 ; a < number ; a++)	printf("*");
	for(i = 0 ; i < number ;i++)
	{
		for( j = 0; j < number ; j++)
		{
			if(c % number == 0)
			{
				printf("|\n");
			}
			if(gamepad[i][j] != 0)
				printf("+");
			else
				printf("-");
			++c;
		}
	}
	printf("|\n");
	for( int a = 0 ; a < number ; a++)	printf("*");
	printf("|\n");
}
void init()
{
	srand(time(0));
	int count = 0;
	count = rand() %(NUMBER / 3);
//		printf("%d",count);		//debug
	int i = 0 ;
	for(  ; i < count+1 ; i++)
	{
		gamepad[rand()%number][rand()%number] = 1;
//		printf("%d",i);

	}
}
void run()
{
	int i , j;
	for( i = 0 ; i < number ; i++)
		for( j = 0 ; j < number ; j++)
		{
			if(i == 0 && j == 0)	//特殊情况:左上角
			{
				if(gamepad[i][j] == 1)		//当前状态为1
				{
					if(gamepad[i][j+1] + gamepad[i+1][j] + gamepad[i+1][j+1] < 2)
						gamepad[i][j] = 0;
					if(gamepad[i][j+1] + gamepad[i+1][j] + gamepad[i+1][j+1] > 3)
						gamepad[i][j] = 0;
				}
				if(gamepad[i][j] == 0)		//当前状态为0
				{
					if(gamepad[i][j+1] + gamepad[i+1][j] + gamepad[i+1][j+1] > 3)
						gamepad[i][j] = 1;
				}
				continue;
			}
			if(i == 0 && j == number-1)	//特殊情况:右上角
			{
				if(gamepad[i][j] == 1)		//当前状态为1
				{
					if(gamepad[i][j-1] + gamepad[i+1][j] + gamepad[i+1][j-1] < 2)
						gamepad[i][j] = 0;
					if(gamepad[i][j-1] + gamepad[i+1][j] + gamepad[i+1][j-1] > 3)
						gamepad[i][j] = 0;
				}
				if(gamepad[i][j] == 0)		//当前状态为0
				{
					if(gamepad[i][j-1] + gamepad[i+1][j] + gamepad[i+1][j-1] > 3)
						gamepad[i][j] = 1;
				}
				continue;
			}
			if(i == number-1 && j == 0)	//特殊情况:左下角
			{
				if(gamepad[i][j] == 1)		//当前状态为1
				{
					if(gamepad[i][j+1] + gamepad[i-1][j] + gamepad[i-1][j+1] < 2)
						gamepad[i][j] = 0;
					if(gamepad[i][j+1] + gamepad[i-1][j] + gamepad[i-1][j+1] > 3)
						gamepad[i][j] = 0;
				}
				if(gamepad[i][j] == 0)		//当前状态为0
				{
					if(gamepad[i][j+1] + gamepad[i-1][j] + gamepad[i-1][j+1] > 3)
						gamepad[i][j] = 1;
				}
				continue;
			}
			if(i == number-1 && j == number-1)	//特殊情况:右下角
			{
				if(gamepad[i][j] == 1)		//当前状态为1
				{
					if(gamepad[i][j-1] + gamepad[i-1][j] + gamepad[i-1][j-1] < 2)
						gamepad[i][j] = 0;
					if(gamepad[i][j-1] + gamepad[i-1][j] + gamepad[i-1][j-1] > 3)
						gamepad[i][j] = 0;
				}
				if(gamepad[i][j] == 0)		//当前状态为0
				{
					if(gamepad[i][j-1] + gamepad[i-1][j] + gamepad[i-1][j-1] > 3)
						gamepad[i][j] = 1;
				}
				continue;
			}
			if(i == 0) 							//特殊情况:第一行
			{
				if(gamepad[i][j] == 1)
				{
					if(gamepad[i][j-1] + gamepad[i+1][j-1] + gamepad[i+1][j] + gamepad[i+1][j+1] + gamepad[i][j+1] < 2)
						gamepad[i][j] = 0;
					if(gamepad[i][j-1] + gamepad[i+1][j-1] + gamepad[i+1][j] + gamepad[i+1][j+1] + gamepad[i][j+1] > 3)
						gamepad[i][j] = 0;
				}
				if(gamepad[i][j] == 0)
				{
					if(gamepad[i][j-1] + gamepad[i+1][j-1] + gamepad[i+1][j] + gamepad[i+1][j+1] + gamepad[i][j+1] > 3)
						gamepad[i][j] = 1;
				}
				continue;
			}
			if(i == number-1) 							//特殊情况:最后一行
			{
				if(gamepad[i][j] == 1)
				{
					if(gamepad[i][j-1] + gamepad[i-1][j-1] + gamepad[i-1][j] + gamepad[i-1][j+1] + gamepad[i][j+1] < 2)
						gamepad[i][j] = 0;
					if(gamepad[i][j-1] + gamepad[i-1][j-1] + gamepad[i-1][j] + gamepad[i-1][j+1] + gamepad[i][j+1] > 3)
						gamepad[i][j] = 0;
				}
				if(gamepad[i][j] == 0)
				{
					if(gamepad[i][j-1] + gamepad[i-1][j-1] + gamepad[i-1][j] + gamepad[i-1][j+1] + gamepad[i][j+1] > 3)
						gamepad[i][j] = 1;
				}
				continue;
			}
			if(j == 0) 							//特殊情况:第一列
			{
				if(gamepad[i][j] == 1)
				{
					if(gamepad[i-1][j] + gamepad[i-1][j+1] + gamepad[i][j+1] + gamepad[i+1][j+1] + gamepad[i+1][j] < 2)
						gamepad[i][j] = 0;
					if(gamepad[i-1][j] + gamepad[i-1][j+1] + gamepad[i][j+1] + gamepad[i+1][j+1] + gamepad[i+1][j] > 3)
						gamepad[i][j] = 0;
				}
				if(gamepad[i][j] == 0)
				{
					if(gamepad[i-1][j] + gamepad[i-1][j+1] + gamepad[i][j+1] + gamepad[i+1][j+1] + gamepad[i+1][j] > 3)
						gamepad[i][j] = 1;
				}
				continue;
			}
			if(j == number-1) 							//特殊情况:最后一列
			{
				if(gamepad[i][j] == 1)
				{
					if(gamepad[i-1][j] + gamepad[i-1][j-1] + gamepad[i][j-1] + gamepad[i+1][j-1] + gamepad[i+1][j] < 2)
						gamepad[i][j] = 0;
					if(gamepad[i-1][j] + gamepad[i-1][j-1] + gamepad[i][j-1] + gamepad[i+1][j-1] + gamepad[i+1][j] > 3)
						gamepad[i][j] = 0;
				}
				if(gamepad[i][j] == 0)
				{
					if(gamepad[i-1][j] + gamepad[i-1][j-1] + gamepad[i][j-1] + gamepad[i+1][j-1] + gamepad[i+1][j] > 3)
						gamepad[i][j] = 1;
				}
				continue;
			}
			if(gamepad[i][j] == 1)						//当前状态为1
			{
				if(   gamepad[i-1][j-1] + gamepad[i][j-1] + gamepad[i+1][j-1] + gamepad[i+1][j]
					+ gamepad[i+1][j+1] + gamepad[i][j+1] + gamepad[i-1][j+1] + gamepad[i-1][j] < 2)
					gamepad[i][j] = 0;
				if(   gamepad[i-1][j-1] + gamepad[i][j-1] + gamepad[i+1][j-1] + gamepad[i+1][j]
					+ gamepad[i+1][j+1] + gamepad[i][j+1] + gamepad[i-1][j+1] + gamepad[i-1][j] > 3)
					gamepad[i][j] = 0;
				continue;
			}
			if(gamepad[i][j] == 0)
			{
				if(   gamepad[i-1][j-1] + gamepad[i][j-1] + gamepad[i+1][j-1] + gamepad[i+1][j]
					+ gamepad[i+1][j+1] + gamepad[i][j+1] + gamepad[i-1][j+1] + gamepad[i-1][j] > 3)
					gamepad[i][j] = 1;
				continue;
			}
		}
}
