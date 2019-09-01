#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/gaussj.c"

void wyzM(float *xw,float *yw, float *w, int n, float alfa, float beta);
float wyzSx(float *xw,float *yw, float *m, int n, float x);
float f1 (float x);
float f2 (float x);

int main() {
	int n = 10; //5, 8, 21
	float xMin = -5.0, xMax = 5.0, h = (xMax - xMin) / (n - 1.0), alfa = 0.0, beta = 0.0, deltaX = 0.01;
	float *xw = vector(1, n);
	float *yw = vector(1, n);
	float *m = vector(1, n);

	FILE *fp1 = fopen("results1.dat", "w");
	FILE *fp2 = fopen("results2.dat", "w");

	for(int i = 1; i <= n; i++) {
		xw[i] = xMin + h * (i-1);
		yw[i] = f1(xw[i]);
		// yw[i] = f2(xw[i]);
	}

	wyzM(xw, yw, m, n, alfa, beta);

	for(int i = 1; i <= n; i++)
		fprintf(fp1,"%10f %10f %10f\n",xw[i], m[i], (f1(xw[i]-deltaX) - 2 * f1(xw[i]) + f1(xw[i] + deltaX))/(deltaX * deltaX));
		// fprintf(fp1,"%10g %10g %10g\n",xw[i], m[i], (f2(xw[i]-deltaX) - 2 * f2(xw[i]) + f2(xw[i] + deltaX)/(deltaX * deltaX)));


	for(float x = xMin + deltaX; x < xMax; x += deltaX) {
    fprintf(fp2, "%10f %10f %10f\n", x, f1(x), wyzSx(xw, yw, m, n, x));
		// fprintf(fp2, "%10f %10f %10f\n", x, f2(x), wyzSx(xw, yw, m, n, x));
  }
  
	fclose(fp1);
	fclose(fp2);
	free_vector(xw, 1, n);
	free_vector(yw, 1, n);
	free_vector(m, 1, n);
	return 0;
}

void wyzM(float *xw,float *yw, float *w, int n, float alfa, float beta) {
	float h = (xw[n] - xw[1])/(n-1);
	float lambda = 0.5;
	float mi = 0.5;
	float **A = matrix(1, n, 1, n);
	float **d = matrix(1, n, 1, 1);
	for(int i = 1;i <= n; i++){
		for(int j = 1;j <=n ;j++){
			A[i][j] = 0.0;
			if((j-1) == i)
				A[i][j] = lambda;
			A[i][i] = 2.0;
			if((j+1) == i)
				A[i][j] = mi;
		}
		d[i][1] = (6.0 / (2 * h)) * ((yw[i+1] - yw[i])/h - (yw[i] - yw[i-1])/h );
	}

	A[1][1] = 1.0;
	A[1][2] = 0.0;
	A[n][n] = 1.0;
	A[n][n-1] = 0.0;
	d[1][1] = alfa;
	d[n][1] = beta;
	gaussj(A, n, d, 1);

	for(int i = 1; i <= n; i++){
		w[i] = d[i][1];
	}
	free_matrix(A, 1, n, 1, n);
	free_matrix(d, 1, n, 1, 1);
}


float wyzSx(float * xw, float * yw, float *m, int n, float x){
	int i;
	float Sx = 0., A, B;
	float h = (xw[n] - xw[1]) / (n-1);
	for(i = 1; i < n + 1; i++){
		
		
		for(i = 2; i <= n; i++){
			if(x >= xw[i-1] && x <= xw[i]){
				A = (yw[i] - yw[i-1])/h - h * (m[i] - m[i-1])/6;
				B = yw[i-1] - m[i-1] * h * h/6;
				Sx = m[i-1] * (pow((xw[i] - x),3))/(6*h) + m[i]*(pow((x-xw[i-1]),3))/(6*h) + A *(x-xw[i-1])+B;
			}
		}
	
	}
	return Sx;
}

float f1 (float x){
	return 1/(1+x*x);
}

float f2(float x){
	return cos(2*x);
}