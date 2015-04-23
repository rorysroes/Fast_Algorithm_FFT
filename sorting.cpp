#include "stdio.h"
#include "time.h"
#include <stdlib.h>
void quick_sort(int s[10],int left,int right);

int main(){
	int s[10]={-1},i,num = 9,a;
	//創造一組亂數
	srand(time(NULL));
	for (int i = 0; i < num; i++){
	s[i]=rand()%100;
	}
	for (i = 0; i < num; i++){
	printf("%d\t",s[i]);
	}
	quick_sort(s,0,num-1);
	printf("\n");
	
	for ( i = 0; i < num; i++){
	printf("%d\t",s[i]);
	}
	printf("\n");

}
//快速排序法
/*給一個標記(a=-1的位置),當數字小於pivot時,標記加一 ,當標記大於pivot時標記記住那個位置
然後for迴圈繼續執行下去,當執行到小於pivot時,此時這個位置與剛剛標記的值交換,當迴圈執行
完畢pivot跟標記點交換,這樣可以已pivot分出左右兩個大於小於pivot的情況 */

void quick_sort(int s[10],int left,int right)
{
	
	if(right>left)
	{   
	    int i,b,a=left-1;
		for (i=left;i<=right;i++){
			
			if(s[i]<=s[right]){
			    a++;
				b=s[i];
				s[i]=s[a];
				s[a]=b;
			}
			printf("\na=%d\ni=%d\n",a,i);
			for (int j = 0; j < 9; j++){
			printf("%d\t",s[j]);
			}
			
		}

    quick_sort(s, left , a-1);
	quick_sort(s, a+1, right);
		
	}
}





















