#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define frand() ((double)rand())/(RAND_MAX+1.0)
#define N 201

int main() {
	double xMin = -4.0, xMax = 4.0, sigma = (xMax - xMin)/16, x0 = 2.0, deltaX = (xMax - xMin) / (N-1.0), x[N], y[N], alfa, beta, ySzum[N];
	double phi[51][N];

	FILE * fp1 = fopen("gramm.dat", "w");

	for(int i = 0; i < N; i++) {
		x[i] = xMin + i * deltaX;
		y[i] = sin((14*M_PI*x[i])/(xMax-xMin))*(exp(-(x[i]-x0) * (x[i]-x0) / (2 * sigma * sigma)) + exp(-(x[i]+x0) * (x[i]+x0) / (2 * sigma * sigma)));
	}

	for(int i = 0; i < N; i++)
		phi[0][i] = 1;

	for(int j = 1; j < 51; j++) {
		double aAlfa = 0, bAlfa = 0, aBeta = 0, bBeta = 0;
		for(int i = 0; i < N; i++) {
			aAlfa += x[i] * phi[j-1][i] * phi[j-1][i];
			bAlfa += phi[j-1][i] * phi[j-1][i];

			aBeta += x[i] * phi[j-2][i] * phi[j-1][i];
			bBeta += phi[j-2][i] * phi[j-2][i];

		}
		alfa = aAlfa/bAlfa;
		if(j != 1)
				beta = aBeta/bBeta;
			else beta = 0;

		for (int i = 0; i < N; i++) {
			phi[j][i] = (x[i] - alfa) * phi[j-1][i] - beta * phi[j-2][i];
		}
	}

	for(int i = 0; i < 7; i++) {
		for(int j = 0; j < N; j++) {
			fprintf(fp1, "%f %f\n", x[j], phi[i][j]/phi[i][0]);
		}
		fprintf(fp1, "\n\n");
	}


	for(int i = 0; i < N; i++) {
		ySzum[i] = y[i] + (frand() - 0.5)/ 5;
	}

	fclose(fp1);

	FILE * fp2 = fopen("m10.dat", "w");
	// FILE * fp2 = fopen("m30.dat", "w");
	// FILE * fp2 = fopen("m50.dat", "w");

	int m = 10;
	// int m = 30;
	// int m = 50;

	double c, s;
	double F;

	for(int k = 0; k < N; k++) {
		F = 0;
		for (int j = 0; j <= m; j++) {
			c = 0;
			s = 0;

			for(int i = 0; i < N ; i++) {
				c += ySzum[i] * phi[j][i];
				s += phi[j][i] * phi[j][i];
			}
			F += c/s * phi[j][k];
		}

		fprintf(fp2, "%f %f %f %f\n", x[k], ySzum[k], y[k], F);
	}

	fclose(fp2);

	return 0;
}