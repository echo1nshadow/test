#include<stdio.h>
#include<time.h>

int main ()
{
   time_t curtime;

   time(&curtime);

   printf("当前时间 = %s", ctime(&curtime));
	printf("%d\n",sizeof(ctime(&curtime)));

   return(0);
}
