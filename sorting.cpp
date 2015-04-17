#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int i,n,*v;
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
    //bubble sort 
    //compare v[i] and v[j]
    //if v[i] > v[j] then v[i] <--> v[j]
    //由左到右,相鄰兩兩比較,較大者往右移
	//最大值會出現在陣列右端
	//遞迴處理尚未排序的n-1個原元素
	for(i=0;i<n;i++)
	{
		if(v[i]>v[i+1])    //相鄰兩兩比較 
		{
			hold = v[i];
			v[i] = v[i+1];
			v[i+1] = hold;
		}
    } 
    for(i=0;i<n;i++)
	{
		printf("%d,",v[i]);
	}
    
}



















