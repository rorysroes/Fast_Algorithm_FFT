#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int SFT(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int FFT_radix_2(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int FFT_radix_3(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int FFT_radix_5(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int Initial(double *x, double *y, int N);
int Print_Complex_Vector(double *x, double *y, int N);

int main()
{
	// y_k = sum(x_n * w^{-kn}, n=0..N-1)
	// w = cos(2*pi/N)+isin(2*pi/N)
	int k ,n ,N=1,q,p,r;
	double *y_r, *y_i, *x_r, *x_i;
	clock_t t1,t2;
	printf("Please input p q r=");
	scanf("%d %d %d", &p,&q,&r);
	for(int i = 0;i<p ;i++)N*=2;    
	for(int i = 0;i<q ;i++)N*=3;    
	for(int i = 0;i<r ;i++)N*=5;    
	printf("N = %d\n", N);                       

	x_r = (double * ) malloc(N*sizeof(double));
	x_i = (double * ) malloc(N*sizeof(double));
	y_r = (double * ) malloc(N*sizeof(double));
	y_i = (double * ) malloc(N*sizeof(double));
	/*
    Initial(x_r, x_i, N);
	t1 = clock();
    SFT(x_r, x_i, y_r, y_i, N);
	t2 = clock();
	printf("%f secs\n",1.0*(t2 -t1)/CLOCKS_PER_SEC);
	Print_Complex_Vector(y_r,y_i, N);
	*/
    Initial(x_r, x_i, N);
	if((N%2) == 0)
	{
		t1 = clock();
		FFT_radix_2(x_r, x_i, y_r, y_i, N);
		t2 = clock();
		printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);	
		system("pause");
		Print_Complex_Vector(y_r, y_i, N);	
	}
	else if((N%3) == 0){
		t1 = clock();
		FFT_radix_3(x_r, x_i, y_r, y_i, N);
		t2 = clock();
		printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);	
		system("pause");
		Print_Complex_Vector(y_r, y_i, N);	
	}
	else if((N%5) == 0){
		t1 = clock();
		FFT_radix_5(x_r, x_i, y_r, y_i, N);
		t2 = clock();
		printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);	
		system("pause");
		Print_Complex_Vector(y_r, y_i, N);	
	}
	else {
		printf("Error");
		return 0;
	}
    return 0;
}
int SFT(double *x_r, double *x_i, double *y_r, double *y_i, int N)
{
	int k, n;
	double w_r, w_i;
	for(k=0;k<N;++k)
	{
		y_r[k] = 0.0;
		y_i[k] = 0.0;
		for(n=0;n<N;n++)
		{
			// w^{-kn}
			// w^{-kn} = cos(-kn*2*pi/N)+ i sin(-kn*2*pi/N)
			w_r = cos(-k*n*2*M_PI/N);
			w_i = sin(-k*n*2*M_PI/N);
			y_r[k] = y_r[k] + x_r[n]*w_r - x_i[n]*w_i;
			y_i[k] = y_i[k] + x_r[n]*w_i + x_i[n]*w_r;
		}
	}
}

int FFT_radix_2(double *x_r, double *x_i, double *y_r, double *y_i, int N)
{
	if(N==1)
	{
		y_r[0] = x_r[0];
		y_i[0] = x_i[0];
	    return 0; 	
	}
	// input : x = x_r + i * x_i
	// output : y = y_r + i * y_i
	int k, n;

	double *even_r, *even_i, *odd_r, *odd_i, w_r, w_i;
    double *even_FT_r, *even_FT_i, *odd_FT_r, *odd_FT_i;

	even_r = (double *) malloc(N*sizeof(double));
	even_i = (double *) malloc(N*sizeof(double));
	odd_r = even_r + N/2; //(double *) malloc(N/2*sizeof(double));
	odd_i = even_i + N/2; //(double *) malloc(N/2*sizeof(double));
	even_FT_r = (double *) malloc(N*sizeof(double));
	even_FT_i = (double *) malloc(N*sizeof(double));
	odd_FT_r = even_FT_r + N/2;//(double *) malloc(N/2*sizeof(double));
	odd_FT_i = even_FT_i + N/2;//(double *) malloc(N/2*sizeof(double));
	
	for(n=0;n<N/2;++n)
	{
		even_r[n] = x_r[2*n];
		even_i[n] = x_i[2*n];
		odd_r[n] = x_r[2*n+1];
		odd_i[n] = x_i[2*n+1];
	}
	//FFT_radix_2(even_r,even_i,even_FT_r,even_FT_i,N/2);
	//FFT_radix_2(odd_r,odd_i,odd_FT_r,odd_FT_i,N/2);
	if((n%2) == 0){
		FFT_radix_2(even_r,even_i,even_FT_r,even_FT_i,N/2);
		FFT_radix_2(odd_r,odd_i,odd_FT_r,odd_FT_i,N/2);
	}
	else if((n%3) == 0){
		FFT_radix_3(even_r,even_i,even_FT_r,even_FT_i,N/2);
	    FFT_radix_3(odd_r,odd_i,odd_FT_r,odd_FT_i,N/2);
	}
	else if(n%5==0){
		FFT_radix_5(even_r,even_i,even_FT_r,even_FT_i,N/2);
		FFT_radix_5(odd_r,odd_i,odd_FT_r,odd_FT_i,N/2);
	}else{
	    FFT_radix_2(even_r,even_i,even_FT_r,even_FT_i,N/2);
		FFT_radix_2(odd_r,odd_i,odd_FT_r,odd_FT_i,N/2);	
	}
	
	for(k=0;k<N/2;++k)
	{
		// w^{-k}
		w_r = cos(-k*2*M_PI/N);
		w_i = sin(-k*2*M_PI/N);
		//printf("N=%d, w_r = %f, w_i = %f\n",N, w_r, w_i);
		y_r[k] = even_FT_r[k] + (w_r*odd_FT_r[k] - w_i*odd_FT_i[k]);
		y_i[k] = even_FT_i[k] + (w_r*odd_FT_i[k] + w_i*odd_FT_r[k]);
		y_r[k+N/2] = even_FT_r[k] - (w_r*odd_FT_r[k] - w_i*odd_FT_i[k]);
		y_i[k+N/2] = even_FT_i[k] - (w_r*odd_FT_i[k] + w_i*odd_FT_r[k]); 
	    
	}
	free(even_r);
	free(even_i);
	free(even_FT_r);
	free(even_FT_i);
	return 0;
}

int FFT_radix_3(double *x_r, double *x_i, double *y_r, double *y_i, int N)
{
	if(N==1)
	{
		y_r[0] = x_r[0];
		y_i[0] = x_i[0];
	    return 0; 	
	}
	// input : x = x_r + i * x_i
	// output : y = y_r + i * y_i
	int k, n;
	double *three_1_r, *three_1_i, *three_2_r, *three_2_i, *three_3_r, *three_3_i,  w_r, w_i;
    double *three_1_FT_r, *three_1_FT_i, *three_2_FT_r, *three_2_FT_i, *three_3_FT_r, *three_3_FT_i;
    
	three_1_r = (double *) malloc(N*sizeof(double));
	three_1_i = (double *) malloc(N*sizeof(double));
	three_2_r = three_1_r + N/3;
	three_2_i = three_1_i + N/3; 
	three_3_r = three_2_r + N/3;
	three_3_i = three_2_i + N/3; 
	three_1_FT_r = (double *) malloc(N*sizeof(double));
	three_1_FT_i = (double *) malloc(N*sizeof(double));
	three_2_FT_r = three_1_FT_r + N/3;
	three_2_FT_i = three_1_FT_i + N/3;
	three_3_FT_r = three_2_FT_r + N/3;
	three_3_FT_i = three_2_FT_i + N/3;
	
	for(n=0;n<N/3;n++)
	{
		three_1_r[n] = x_r[3*n];
		three_1_i[n] = x_i[3*n];
		three_2_r[n] = x_r[3*n+1];
		three_2_i[n] = x_i[3*n+1];
		three_3_r[n] = x_r[3*n+2];
	    three_3_i[n] = x_i[3*n+2];
	}
	
	//FFT_radix_3(three_1_r,three_1_i,three_1_FT_r,three_1_FT_i,N/3);
	//FFT_radix_3(three_2_r,three_2_i,three_2_FT_r,three_2_FT_i,N/3);
	//FFT_radix_3(three_3_r,three_3_i,three_3_FT_r,three_3_FT_i,N/3);
	
	if((n%5) == 0){
	  FFT_radix_5(three_1_r,three_1_i,three_1_FT_r,three_1_FT_i,N/3);
	  FFT_radix_5(three_2_r,three_2_i,three_2_FT_r,three_2_FT_i,N/3);
	  FFT_radix_5(three_3_r,three_3_i,three_3_FT_r,three_3_FT_i,N/3);
	}
	else if((n%3) == 0){
	  FFT_radix_3(three_1_r,three_1_i,three_1_FT_r,three_1_FT_i,N/3);
	  FFT_radix_3(three_2_r,three_2_i,three_2_FT_r,three_2_FT_i,N/3);
	  FFT_radix_3(three_3_r,three_3_i,three_3_FT_r,three_3_FT_i,N/3);
	}	
	else if((n%2) == 0){
	  FFT_radix_2(three_1_r,three_1_i,three_1_FT_r,three_1_FT_i,N/3);
	  FFT_radix_2(three_2_r,three_2_i,three_2_FT_r,three_2_FT_i,N/3);
	  FFT_radix_2(three_3_r,three_3_i,three_3_FT_r,three_3_FT_i,N/3);
    }else{
      FFT_radix_3(three_1_r,three_1_i,three_1_FT_r,three_1_FT_i,N/3);
	  FFT_radix_3(three_2_r,three_2_i,three_2_FT_r,three_2_FT_i,N/3);
	  FFT_radix_3(three_3_r,three_3_i,three_3_FT_r,three_3_FT_i,N/3);
	}
	
	for(k=0;k<N/3;++k)
	{
		//wN^{-3kn} = cos(-n*3*pi/N)+ i sin(-kn*3*pi/N)
		//f(k) = sum((x_r + i * x_i) * wN^{-3kn})
		//wN^{-3k(n+1)} = cos(-(n+1)*3*pi/N)+ i sin(-k(n+1)*3*pi/N)
		//f(k) = sum((x_r + i * x_i) * wN^{-3k(n+1)})
		//wN^{-3k(n+2)} = cos(-(n+2)*3*pi/N)+ i sin(-k(n+2)*3*pi/N)
		//f(k) = sum((x_r + i * x_i) * wN^{-3k(n+1)})
		
		w_r = cos(-k*2*M_PI/N);
		w_i = sin(-k*2*M_PI/N);
		y_r[k] = three_1_FT_r[k] + w_r*three_1_FT_r[k+N/3] - w_i*three_1_FT_i[k+N/3];
		y_i[k] = three_1_FT_i[k] + w_r*three_1_FT_i[k+N/3] + w_i*three_1_FT_r[k+N/3];
		w_r = cos(-k*4*M_PI/N);
		w_i = sin(-k*4*M_PI/N);
		y_r[k] += w_r*three_1_FT_r[k+2*N/3] - w_i*three_1_FT_i[k+2*N/3];
		y_i[k] += w_r*three_1_FT_i[k+2*N/3] + w_i*three_1_FT_r[k+2*N/3];
		
		//f(k + N/3)
		w_r = cos(-(k+N/3)*2*M_PI/N);
		w_i = sin(-(k+N/3)*2*M_PI/N);
		y_r[k+N/3] = three_1_FT_r[k] + w_r*three_1_FT_r[k+N/3] - w_i*three_1_FT_i[k+N/3];
		y_i[k+N/3] = three_1_FT_i[k] + w_r*three_1_FT_i[k+N/3] + w_i*three_1_FT_r[k+N/3];
		w_r = cos(-(k+N/3)*4*M_PI/N);
		w_i = sin(-(k+N/3)*4*M_PI/N);
		y_r[k+N/3] += w_r*three_1_FT_r[k+2*N/3] - w_i*three_1_FT_i[k+2*N/3];
		y_i[k+N/3] += w_r*three_1_FT_i[k+2*N/3] + w_i*three_1_FT_r[k+2*N/3];
		
		//f(k + N/3)
		w_r = cos(-(k+2*N/3)*2*M_PI/N);
		w_i = sin(-(k+2*N/3)*2*M_PI/N);
		y_r[k+2*N/3] = three_1_FT_r[k] + w_r*three_1_FT_r[k+N/3] - w_i*three_1_FT_i[k+N/3];
		y_i[k+2*N/3] = three_1_FT_i[k] + w_r*three_1_FT_i[k+N/3] + w_i*three_1_FT_r[k+N/3] ;
		w_r = cos(-(k+2*N/3)*4*M_PI/N);
		w_i = sin(-(k+2*N/3)*4*M_PI/N);
		y_r[k+2*N/3] += w_r*three_1_FT_r[k+2*N/3] - w_i*three_1_FT_i[k+2*N/3];
		y_i[k+2*N/3] += w_r*three_1_FT_i[k+2*N/3] + w_i*three_1_FT_r[k+2*N/3]; 
	}
	
	free(three_1_r);
	free(three_1_i);
	free(three_1_FT_r);
	free(three_1_FT_i);

	return 0;
}
int FFT_radix_5(double *x_r, double *x_i, double *y_r, double *y_i, int N)
 {
 
	if(N==1)
	{
		y_r[0] = x_r[0];
		y_i[0] = x_i[0];
	    return 0; 	
	}
	// input : x = x_r + i * x_i
	// output : y = y_r + i * y_i
	int k, n;
	double *five_1r, *five_1i, *five_2r, *five_2i, *five_3r, *five_3i, *five_4r, *five_4i, *five_5r, *five_5i, w_r, w_i;
    double *five_1_FTr, *five_1_FTi, *five_2_FTr, *five_2_FTi, *five_3_FTr, *five_3_FTi, *five_4_FTr, *five_4_FTi, *five_5_FTr, *five_5_FTi;

	five_1r = (double *) malloc(N*sizeof(double));
	five_1i = (double *) malloc(N*sizeof(double));
	five_2r = five_1r + N/5;
	five_2i = five_1i + N/5; 
	five_3r = five_2r + N/5;
	five_3i = five_2i + N/5;
	five_4r = five_3r + N/5;
	five_4i = five_3i + N/5;
	five_5r = five_4r + N/5;
	five_5i = five_4i + N/5;
	five_1_FTr = (double *) malloc(N*sizeof(double));
	five_1_FTi = (double *) malloc(N*sizeof(double));
	five_2_FTr = five_1_FTr + N/5;
	five_2_FTi = five_1_FTi + N/5;
	five_3_FTr = five_2_FTr + N/5;
	five_3_FTi = five_2_FTi + N/5;
	five_4_FTr = five_3_FTr + N/5;
	five_4_FTi = five_3_FTi + N/5;
	five_5_FTr = five_4_FTr + N/5;
	five_5_FTi = five_4_FTi + N/5;	
	
	
	for(n=0;n<N/5;n++)
	{
		five_1r[n] = x_r[5*n];
		five_1i[n] = x_i[5*n];
		five_2r[n] = x_r[5*n+1];
		five_2i[n] = x_i[5*n+1];
		five_3r[n] = x_r[5*n+2];
	    five_3i[n] = x_i[5*n+2];
		five_4r[n] = x_r[5*n+3];
	    five_4i[n] = x_i[5*n+3];	    
		five_5r[n] = x_r[5*n+4];
	    five_5i[n] = x_i[5*n+4];	     
	}
	
	//FFT_radix_5(five_1r, five_1i,five_1_FTr, five_1_FTi,N/5);
	//FFT_radix_5(five_2r, five_2i,five_2_FTr, five_2_FTi,N/5);
	//FFT_radix_5(five_3r, five_3i,five_3_FTr, five_3_FTi,N/5);
	//FFT_radix_5(five_4r, five_4i,five_4_FTr, five_4_FTi,N/5);
	//FFT_radix_5(five_5r, five_5i,five_5_FTr, five_5_FTi,N/5);
	
	if((n%5) == 0){
		FFT_radix_5(five_1r, five_1i,five_1_FTr, five_1_FTi,N/5);
		FFT_radix_5(five_2r, five_2i,five_2_FTr, five_2_FTi,N/5);
		FFT_radix_5(five_3r, five_3i,five_3_FTr, five_3_FTi,N/5);
		FFT_radix_5(five_4r, five_4i,five_4_FTr, five_4_FTi,N/5);
		FFT_radix_5(five_5r, five_5i,five_5_FTr, five_5_FTi,N/5);
	}	
	else if((n%3) == 0){
		FFT_radix_3(five_1r, five_1i,five_1_FTr, five_1_FTi,N/5);
		FFT_radix_3(five_2r, five_2i,five_2_FTr, five_2_FTi,N/5);
		FFT_radix_3(five_3r, five_3i,five_3_FTr, five_3_FTi,N/5);
		FFT_radix_3(five_4r, five_4i,five_4_FTr, five_4_FTi,N/5);
		FFT_radix_3(five_5r, five_5i,five_5_FTr, five_5_FTi,N/5);
	}
	else if((n%2) == 0){
		FFT_radix_2(five_1r, five_1i,five_1_FTr, five_1_FTi,N/5);
		FFT_radix_2(five_2r, five_2i,five_2_FTr, five_2_FTi,N/5);
		FFT_radix_2(five_3r, five_3i,five_3_FTr, five_3_FTi,N/5);
		FFT_radix_2(five_4r, five_4i,five_4_FTr, five_4_FTi,N/5);
		FFT_radix_2(five_5r, five_5i,five_5_FTr, five_5_FTi,N/5);
	}else{
		FFT_radix_5(five_1r, five_1i,five_1_FTr, five_1_FTi,N/5);
		FFT_radix_5(five_2r, five_2i,five_2_FTr, five_2_FTi,N/5);
		FFT_radix_5(five_3r, five_3i,five_3_FTr, five_3_FTi,N/5);
		FFT_radix_5(five_4r, five_4i,five_4_FTr, five_4_FTi,N/5);
		FFT_radix_5(five_5r, five_5i,five_5_FTr, five_5_FTi,N/5);
		
	}
    for(k=0;k<N/5;++k)
	{
		//wN^{-5kn} = cos(-n*5*pi/N)+ i sin(-kn*5*pi/N)
		//f(k) = sum((x_r + i * x_i) * wN^{-5kn})
		//wN^{-5k(n+1)} = cos(-(n+1)*5*pi/N)+ i sin(-k(n+1)*5*pi/N)
		//f(k) = sum((x_r + i * x_i) * wN^{-3k(n+1)})
		//wN^{-5k(n+2)} = cos(-(n+2)*5*pi/N)+ i sin(-k(n+2)*5*pi/N)
		//f(k) = sum((x_r + i * x_i) * wN^{-3k(n+2)})
		//wN^{-5k(n+3)} = cos(-(n+3)*5*pi/N)+ i sin(-k(n+3)*5*pi/N)
		//f(k) = sum((x_r + i * x_i) * wN^{-3k(n+3)})
		//wN^{-5k(n+3)} = cos(-(n+4)*5*pi/N)+ i sin(-k(n+4)*5*pi/N)
		//f(k) = sum((x_r + i * x_i) * wN^{-3k(n+4)})
				
		w_r = cos(-k*2*M_PI/N);
		w_i = sin(-k*2*M_PI/N);
		y_r[k] = five_1_FTr[k] + w_r*five_1_FTr[k+N/5] - w_i*five_1_FTi[k+N/5];
		y_i[k] = five_1_FTi[k] + w_r*five_1_FTi[k+N/5] + w_i*five_1_FTr[k+N/5];
		w_r = cos(-k*4*M_PI/N);
		w_i = sin(-k*4*M_PI/N);
		y_r[k] += w_r*five_1_FTr[k+2*N/5] - w_i*five_1_FTi[k+2*N/5]; 
		y_i[k] += w_r*five_1_FTi[k+2*N/5] + w_i*five_1_FTr[k+2*N/5];
		w_r = cos(-k*6*M_PI/N);
		w_i = sin(-k*6*M_PI/N);
		y_r[k] += w_r*five_1_FTr[k+3*N/5] - w_i*five_1_FTi[k+3*N/5];
		y_i[k] += w_r*five_1_FTi[k+3*N/5] + w_i*five_1_FTr[k+3*N/5];
		w_r = cos(-k*8*M_PI/N);
		w_i = sin(-k*8*M_PI/N);
		y_r[k] += w_r*five_1_FTr[k+4*N/5] - w_i*five_1_FTi[k+4*N/5];
		y_i[k] += w_r*five_1_FTi[k+4*N/5] + w_i*five_1_FTr[k+4*N/5];
		
		w_r = cos(-(k+N/5)*2*M_PI/N);
		w_i = sin(-(k+N/5)*2*M_PI/N);
		y_r[k+N/5] = five_1_FTr[k] + w_r*five_1_FTr[k+N/5] - w_i*five_1_FTi[k+N/5];
		y_i[k+N/5] = five_1_FTi[k] + w_r*five_1_FTi[k+N/5] + w_i*five_1_FTr[k+N/5];
		w_r = cos(-(k+N/5)*4*M_PI/N);
		w_i = sin(-(k+N/5)*4*M_PI/N);
		y_r[k+N/5] += w_r*five_1_FTr[k+2*N/5] - w_i*five_1_FTi[k+2*N/5]; 
		y_i[k+N/5] += w_r*five_1_FTi[k+2*N/5] + w_i*five_1_FTr[k+2*N/5];
		w_r = cos(-(k+N/5)*6*M_PI/N);
		w_i = sin(-(k+N/5)*6*M_PI/N);
		y_r[k+N/5] += w_r*five_1_FTr[k+3*N/5] - w_i*five_1_FTi[k+3*N/5];
		y_i[k+N/5] += w_r*five_1_FTi[k+3*N/5] + w_i*five_1_FTr[k+3*N/5];
		w_r = cos(-(k+N/5)*8*M_PI/N);
		w_i = sin(-(k+N/5)*8*M_PI/N);
		y_r[k+N/5] += w_r*five_1_FTr[k+4*N/5] - w_i*five_1_FTi[k+4*N/5];
		y_i[k+N/5] += w_r*five_1_FTi[k+4*N/5] + w_i*five_1_FTr[k+4*N/5];
		
		w_r = cos(-(k+2*N/5)*2*M_PI/N);
		w_i = sin(-(k+2*N/5)*2*M_PI/N);
		y_r[k+2*N/5] = five_1_FTr[k] + w_r*five_1_FTr[k+N/5] - w_i*five_1_FTi[k+N/5];
		y_i[k+2*N/5] = five_1_FTi[k] + w_r*five_1_FTi[k+N/5] + w_i*five_1_FTr[k+N/5];
		w_r = cos(-(k+2*N/5)*4*M_PI/N);
		w_i = sin(-(k+2*N/5)*4*M_PI/N);
		y_r[k+2*N/5] += w_r*five_1_FTr[k+2*N/5] - w_i*five_1_FTi[k+2*N/5]; 
		y_i[k+2*N/5] += w_r*five_1_FTi[k+2*N/5] + w_i*five_1_FTr[k+2*N/5];
		w_r = cos(-(k+2*N/5)*6*M_PI/N);
		w_i = sin(-(k+2*N/5)*6*M_PI/N);
		y_r[k+2*N/5] += w_r*five_1_FTr[k+3*N/5] - w_i*five_1_FTi[k+3*N/5];
		y_i[k+2*N/5] += w_r*five_1_FTi[k+3*N/5] + w_i*five_1_FTr[k+3*N/5];
		w_r = cos(-(k+2*N/5)*8*M_PI/N);
		w_i = sin(-(k+2*N/5)*8*M_PI/N);
		y_r[k+2*N/5] += w_r*five_1_FTr[k+4*N/5] - w_i*five_1_FTi[k+4*N/5];
		y_i[k+2*N/5] += w_r*five_1_FTi[k+4*N/5] + w_i*five_1_FTr[k+4*N/5];
		
		w_r = cos(-(k+3*N/5)*2*M_PI/N);
		w_i = sin(-(k+3*N/5)*2*M_PI/N);
		y_r[k+3*N/5] = five_1_FTr[k] + w_r*five_1_FTr[k+N/5] - w_i*five_1_FTi[k+N/5];
		y_i[k+3*N/5] = five_1_FTi[k] + w_r*five_1_FTi[k+N/5] + w_i*five_1_FTr[k+N/5];
		w_r = cos(-(k+3*N/5)*4*M_PI/N);
		w_i = sin(-(k+3*N/5)*4*M_PI/N);
		y_r[k+3*N/5] += w_r*five_1_FTr[k+2*N/5] - w_i*five_1_FTi[k+2*N/5]; 
		y_i[k+3*N/5] += w_r*five_1_FTi[k+2*N/5] + w_i*five_1_FTr[k+2*N/5];
		w_r = cos(-(k+3*N/5)*6*M_PI/N);
		w_i = sin(-(k+3*N/5)*6*M_PI/N);
		y_r[k+3*N/5] += w_r*five_1_FTr[k+3*N/5] - w_i*five_1_FTi[k+3*N/5];
		y_i[k+3*N/5] += w_r*five_1_FTi[k+3*N/5] + w_i*five_1_FTr[k+3*N/5];
		w_r = cos(-(k+3*N/5)*8*M_PI/N);
		w_i = sin(-(k+3*N/5)*8*M_PI/N);
		y_r[k+3*N/5] += w_r*five_1_FTr[k+4*N/5] - w_i*five_1_FTi[k+4*N/5];
		y_i[k+3*N/5] += w_r*five_1_FTi[k+4*N/5] + w_i*five_1_FTr[k+4*N/5];
		
		w_r = cos(-(k+4*N/5)*2*M_PI/N);
		w_i = sin(-(k+4*N/5)*2*M_PI/N);
		y_r[k+4*N/5] = five_1_FTr[k] + w_r*five_1_FTr[k+N/5] - w_i*five_1_FTi[k+N/5];
		y_i[k+4*N/5] = five_1_FTi[k] + w_r*five_1_FTi[k+N/5] + w_i*five_1_FTr[k+N/5];
		w_r = cos(-(k+4*N/5)*4*M_PI/N);
		w_i = sin(-(k+4*N/5)*4*M_PI/N);
		y_r[k+4*N/5] += w_r*five_1_FTr[k+2*N/5] - w_i*five_1_FTi[k+2*N/5]; 
		y_i[k+4*N/5] += w_r*five_1_FTi[k+2*N/5] + w_i*five_1_FTr[k+2*N/5];
		w_r = cos(-(k+4*N/5)*6*M_PI/N);
		w_i = sin(-(k+4*N/5)*6*M_PI/N);
		y_r[k+4*N/5] += w_r*five_1_FTr[k+3*N/5] - w_i*five_1_FTi[k+3*N/5];
		y_i[k+4*N/5] += w_r*five_1_FTi[k+3*N/5] + w_i*five_1_FTr[k+3*N/5];
		w_r = cos(-(k+4*N/5)*8*M_PI/N);
		w_i = sin(-(k+4*N/5)*8*M_PI/N);
		y_r[k+4*N/5] += w_r*five_1_FTr[k+4*N/5] - w_i*five_1_FTi[k+4*N/5];
		y_i[k+4*N/5] += w_r*five_1_FTi[k+4*N/5] + w_i*five_1_FTr[k+4*N/5];
	}
	
	free(five_1r);
	free(five_1i);
	free(five_1_FTr);
	free(five_1_FTi);
	
	return 0;
	
}

int Initial(double *x, double *y, int N)
{
	int n;
	for(n=0;n<N;++n)
	{
		x[n] = n;
		y[n] = 0;
	}
}

int Print_Complex_Vector(double *x, double *y, int N)
{
	int n;
	for(n=0;n<N;++n)
	{
	 	if (y[n] >=0) printf("%d : %f +%f i\n", n, x[n], y[n]);
		else printf("%d : %f %f i\n", n, x[n], y[n]);
	}
}

