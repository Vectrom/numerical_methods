#include <math.h>
#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/four1.c"

#define max(X,Y) ((X)>(Y)? (X):(Y))

double randDelta();

int main() {
	FILE * fp = fopen("result.dat", "w");

	for (int k = 8; k <= 12; k += 2) {
		int n = pow(2, k);
		float T = 1.0;
		float tMax = 3 * T;
		float dt = tMax/n;
		float sigma = T/20;
		float *f, *g1, *g2, *fZab;
		f = vector(1, 2 * n);
		fZab = vector(1, 2 * n);
		g1 = vector(1, 2 * n);
		g2 = vector(1, 2 * n);

		for(int i = 1; i <= n; i++) {
			float ti = dt * (i-1);
			f[2 * i - 1] = fZab[2 * i - 1] = sin((2 * M_PI / T) * ti) +  sin(2 * (2 * M_PI / T) * ti) + sin(3 * (2 * M_PI / T) * ti) + randDelta();
			g1[2 * i - 1] = g2[2 * i - 1] = (1.0 / (sigma * sqrt(2 * M_PI))) * exp(-(ti * ti) / (2* sigma * sigma));
			f[2 * i] = fZab[2 * i] = g1[2 * i] = g2[2 * i] = 0;

		}


		four1(f, n, 1);
		four1(g1, n, 1);
		four1(g2, n, -1);

		for (int i = 1; i <= n; i++) {
			float a1 = f[2 * i - 1];
			float b1 = f[2 * i];
			float a2 = g1[2 * i - 1] + g2[2 * i - 1];
			float b2 = g1[2 * i] + g2[2 * i];
			f[2 * i - 1] = a1 * a2 - b1 * b2;
			f[2 * i] = a1 * b2 + a2 * b1;
		}

		four1(f, n, -1);

		float maxElem = fabs(f[1]);

		for (int i = 2; i <= n; i++) 
			maxElem = max(fabs(maxElem), fabs(f[2*i-1])); 

		for (int i = 1; i <= n; i++) {
			float ti = dt * (i-1);
			fprintf(fp, "%15g %15g %15g %15g\n", ti, sin((2 * M_PI / T) * ti) +  sin(2 * (2 * M_PI / T) * ti) + sin(3 * (2 * M_PI / T) * ti), fZab[2*i-1], 2.5 * f[2*i-1] / maxElem);
		}
		fprintf(fp, "\n\n");

		free_vector(f, 1, 2 * n);
		free_vector(fZab, 1, 2 * n);
		free_vector(g1, 1, 2 * n);
		free_vector(g2, 1, 2 * n);
	}

	fclose(fp);

	return 0;
}

double randDelta() {
	return ((double) rand()) / RAND_MAX  - 0.5;
}
