#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int SFT(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int FFT(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int Generate_N(int p, int q, int r);
int Initial(double *x, double *y, int N);
int Print_Complex_Vector(double *x, double *y, int N);

int main()
{
	// y_k = sum(x_n * w^{-kn}, n=0..N-1)
	// w = cos(2*pi/N)+isin(2*pi/N)
	int k ,n ,N, p, q, r;
	double *y_r, *y_i, *x_r, *x_i, w_r, w_i;
	clock_t t1,t2;
	//input N
	printf("Please input p q r=");
	scanf("%d %d %d", &p, &q, &r);    
	N = Generate_N(p, q, r);
	printf("N=2^%d 3^%d 5^%d = %d\n", p, q, r, N);                       
	//N = 1 << p;                     //移位算子 2^p ,左移 p 個位置(ex:p=4 => 1= 0001 => 1000 = 16)  
	//printf("N=%d\n",N);
	//create memory for x and y
	x_r = (double * ) malloc(N*sizeof(double));
	x_i = (double * ) malloc(N*sizeof(double));
	y_r = (double * ) malloc(N*sizeof(double));
	y_i = (double * ) malloc(N*sizeof(double));
	
    Initial(x_r, x_i, N);
	t1 = clock();
    SFT(x_r, x_i, y_r, y_i, N);
	t2 = clock();
	printf("%f secs\n",1.0*(t2 -t1)/CLOCKS_PER_SEC);
	//Print_Complex_Vector(y_r,y_i, N);
	
	Initial(x_r, x_i, N);
	t1 = clock();
	FFT(x_r, x_i, y_r, y_i, N);
    t2 = clock();
    printf("%f secs\n",1.0*(t2 -t1)/CLOCKS_PER_SEC);
    //Print_Complex_Vector(y_r,y_i, N);
    
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
int FFT(double *x_r, double *x_i, double *y_r, double *y_i, int N)
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
	//double *u_r, *u_i, *v_r, *v_i, w_r, w_i;
	double *even_r, *even_i, *odd_r, *odd_i, w_r, w_i;
    double *even_FT_r, *even_FT_i, *odd_FT_r, *odd_FT_i;
    
    //開8個記憶體 
	even_r = (double *) malloc(N*sizeof(double));
	even_i = (double *) malloc(N*sizeof(double));
	//一次開N個 
	odd_r = even_r + N/2; //(double *) malloc(N/2*sizeof(double)); 
	odd_i = even_i + N/2; //(double *) malloc(N/2*sizeof(double));
	even_FT_r = (double *) malloc(N*sizeof(double));
	even_FT_i = (double *) malloc(N*sizeof(double));
	odd_FT_r = even_FT_r + N/2;//(double *) malloc(N/2*sizeof(double));
	odd_FT_i = even_FT_i + N/2;//(double *) malloc(N/2*sizeof(double));
	for(n=0;n<N/2;n++)
	{
		even_r[n] = x_r[2*n];
		even_i[n] = x_i[2*n];
		odd_r[n] = x_r[2*n+1];
		odd_i[n] = x_i[2*n+1];
	}
	FFT(even_r,even_i,even_FT_r,even_FT_i,N/2);
	FFT(odd_r,odd_i,odd_FT_r,odd_FT_i,N/2);
	
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
	//把記憶體還作業系統 
	free(even_r);
	free(even_i);
	free(even_FT_r);
	free(even_FT_i);
	/*
	for(k=N/2;k<N-1;++k)
	{
		// w^{-k}
		w_r = cos(-k*2*M_PI/N);
		w_i = sin(-k*2*M_PI/N);
		y_r[k] = even_r[k-N/2] + w_r*odd_r[k-N/2] - w_i*odd_i[K-N/2];
		y_i[k] = even_i[k-N/2] + w_r*odd_i[k-N/2] + w_i*odd_r[k-N/2];
	}	
	*/
	/*
	u_r = (double * ) malloc(N*sizeof(double));
	u_i = (double * ) malloc(N*sizeof(double));
	v_r = (double * ) malloc(N*sizeof(double));
	v_i = (double * ) malloc(N*sizeof(double));
	
	for(n=0;n<N/2;n++)
	{
		u_r[n] = x_r[2*n];
		u_i[n] = x_i[2*n];
		u_r[n+N/2] = x_r[2*n+1];
		u_i[n+N/2] = x_i[2*n+1];
	}
	FFT(u_r, u_i, v_r, v_i, N/2);
	FFT(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2);
	*/
	return 0;
}
int Generate_N(int p, int q, int r)
{
	int N = 1,i;
	// N = 2^p 3^q 5^r
	for(i=0;i<p;i++) N = N * 2;
	for(i=0;i<q;i++) N = N * 3;
	for(i=0;i<r;i++) N = N * 5;
	return N;
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













