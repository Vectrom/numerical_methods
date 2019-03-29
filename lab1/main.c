#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/gaussj.c"

#define N 400 

int main(void) {
	double a = 1.0;
	double v0 = 0;
	double h = 0.1;
	double w = 1.0;
	double wh = w*w*h*h-2;
	float **A,**b;

	A = matrix(1, N, 1, N);
	b = matrix(1, N, 1, 1);
	
	for(int i=1; i<=N; ++i){
		b[i][1] = 0.0;
		for(int j=1; j<=N; ++j)
			A[i][j] = 0.0;
	}

	b[1][1] = a;
	b[2][1] = v0 * h;
	A[2][1] = -1.0;
	
	for(int i=1; i<=N; ++i)
		A[i][i] = 1.0;

	for(int i=3; i<=N; ++i) {
		A[i][i-1] = wh;
		A[i][i-2] = 1.0;
	}
	
	gaussj(A,N,b,1);

	FILE * fp;
	fp = fopen("result.dat", "w");

	for(int i=1; i<=N; ++i)
		fprintf(fp, "%f %g\n",  (i-1)*h, b[i][1]); 
    
    fclose(fp);

	free_matrix(A,1,N,1,N);
	free_matrix(b,1,N,1,1);    
	
	return 0;
}

