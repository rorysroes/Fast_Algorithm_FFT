#include "stdio.h"
#include "time.h"
#include <stdlib.h>

int main(){
	int s[10]={-1},num=5;int a=-1,b=0,i;
	srand(time(NULL));
	for (int i = 0; i < num; i++){
		s[i]=rand()%1000;  //make 0-99 random number
	}
	for (i = 0; i < num; i++){
		printf("%d\t",s[i]); 
	}
	for (i=0;i<num;i++){
		
		/*if(s[i]>s[num-1]){
			//a==0?a=0:a++;
		}
		else {*/
		if(s[i]<=s[num-1]){
			a++;
			if(i!=0 ){
				
				b=s[i];
				s[i]=s[a];
				s[a]=b;
				
			}
		
		}
		printf("\na=%d\ni=%d\n",a,i);
		for (int j = 0; j < num; j++){
			printf("%d\t",s[j]); 
		}
		
	}
	if(b==0){
		b=s[i];
		s[i]=s[a];
		s[a]=b;
	}
	printf("\n");
	for ( i = 0; i < num; i++){
		printf("%d\t",s[i]); 
	}
}
