#include<stdio.h>
#include<unistd.h>
#define SIZE 40

void display();
void init();
void run();
void turnleft();
void turnright();
void go();


int i = 0 ;
int j = 0 ;
int direction = 1;			//1:上  2:左  3:下  4:右
int pad[SIZE][SIZE*3] = {0};
int main()
{
	init();
	while(1)
	{
		display();
		run();
		usleep(300000);
	}
}

void display()
{
	system("clear");
	int a = 0 ; 
	int b = 0;
	for( a = 0 ; a < SIZE ; a++)
	{
		for( b = 0 ; b < SIZE * 3; b++)
		{
			if(pad[a][b] == 1)
			printf("*");
			else
			printf("-");
		}
		printf("\n");
	}
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
		direction = 4;
		return ;
	}
	if(direction == 4)
	{
		direction = 1;
		return ;
	}
}
void turnright()
{
	if(direction == 1)
	{
		direction = 4;
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
	if(direction == 4)
	{
		direction = 3;
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
	if(direction == 1)
	{
		x = i-1;
		y = j;
	}
	if(direction == 2)
	{
		x = i;
		y = j-1;
	}
	if(direction == 3)
	{
		x = i+1;
		y = j;
	}
	if(direction == 4)
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
		direction = (direction+2) % 4;
	}
	if(j < 0)
	{
		j = temp2;
		direction = (direction+2) % 4;
	}
	if(i > SIZE)
	{
		i = temp1;
		direction = (direction+2) % 4;
	}
	if(j > SIZE*3)
	{
		j = temp2;
		direction = (direction+2) % 4;
	}
}

		

	
