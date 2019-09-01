#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f1(double x);
double f2(double x);
double f3(double x);
void Romberg(double ** D, int n, double a, double b, double (*f)(double), const char* filename);
double ** allocTriangleArray(int n);
void freeArray(double ** D, int n);

int main() {
	double ** D1 = allocTriangleArray(8);
	double ** D2 = allocTriangleArray(16);
	double ** D3 = allocTriangleArray(8);

	Romberg(D1, 7, 0, 1, f1, "f1.dat");
	Romberg(D2, 15, -1, 1, f2, "f2.dat");
	Romberg(D3, 7, 0, 1, f3, "f3.dat");

	freeArray(D1, 8);
	freeArray(D2, 16);
	freeArray(D3, 8);

	return 0;
}


double f1(double x) {
	if(fabs(x) < 0.0000001)
		x += 0.0000001;
	return sin(x)/x;
}

double f2(double x) {
	if(fabs(x) < 0.0000001)
		x += 0.0000001;
	return (cos(x) - exp(x)) / sin(x);
}

double f3(double x) {
	if(fabs(x) < 0.0000001)
		x += 0.0000001;
	return exp(-1/x)/x;
}

void Romberg(double ** D, int n, double a, double b, double (*f)(double), const char * filename) {
	FILE * fp = fopen(filename, "w");

	D[0][0] = 0.5 * (b - a) * (f(a) + f(b));

	for(int i = 1; i <= n; i++) {
		double hw = (b-a) / pow(2, i);
		double sum = 0;

		for(int j = 1; j <= pow(2, i-1); j++) 
			sum += f(a + (2 * j-1) * hw);

		D[i][0] = 0.5 * D[i-1][0] + hw * sum;
	}

	for(int k = 1; k <= n; k++) {
		for(int w = k; w <= n; w++)
			D[w][k] = (pow(4, k) * D[w][k-1] - D[w-1][k-1]) / (pow(4, k) - 1);
	}

	for(int w = 0; w <= n; w++) 
		fprintf(fp, "%d %.10lf %.10lf\n", w, D[w][0], D[w][w]);

	fclose(fp);

}

double ** allocTriangleArray(int n){
	double ** D = malloc(n * sizeof(double* ));
	for(int i = 0; i < n; i++)
		D[i] = malloc((i+1) * sizeof(double));
	return D;
}

void freeArray(double ** D, int n) {
	for(int i = 0; i < n; i++)
		free(D[i]);
	free(D);
}