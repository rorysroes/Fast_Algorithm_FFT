#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i,n,*v;
	time_t T=1;
	int hold;
	srand(time(&T));
	n = 10;
	v = (int*) malloc(n * sizeof(int));
	for(i=0;i<n;i++)
	{
		v[i] = rand() % 100;
		printf("%d,",v[i]);
	}
	printf("\n");
	
	


	
}



















