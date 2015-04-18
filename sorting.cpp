#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int i,j,n,*v;
	time_t T=1;
	int hold;
	//創造n個隨機整數
	
	srand(time(&T));  //把現在時間當做隨機引數,不然會是固定的一組數列 
	n = 10;
	v = (int*) malloc(n * sizeof(int));
	for(i=0;i<n;i++)
	{
		v[i] = rand() % 100;
		printf("%d,",v[i]);
	}
	printf("\n");

	
}



















