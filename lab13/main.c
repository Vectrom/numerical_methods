#include <math.h>
#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/bessi0.c"
#include "/opt/NR/numerical_recipes.c/gauher.c"

int main() {
	double sigma = 1./sqrt(2);
	
	FILE * fp = fopen("results.dat", "w");
	
	for(int n = 5; n <= 35; n+=5) {
		for(double x20 = 0.1; x20 <= 6.0; x20 += 0.1) {
			float * R10 = vector(1, 2);
			float * R20 = vector(1, 2);
			R10[1] = 0;
			R10[2] = 0;
			R20[1] = x20;
			R20[2] = 0;

			double r0 = sqrt(R10[1] * R10[1] + R10[2] * R10[2]) + sqrt(R20[1] * R20[1] + R20[2] * R20[2]);
			
			double Vdok = (2 * M_PI) * (2 * M_PI) * pow(sigma, 4) * sqrt(M_PI)/(2 * sigma) * exp(-(r0 * r0) / (8 * sigma * sigma)) * bessi0((r0 * r0) / (8 * sigma * sigma));

			float * x1 = vector(1, n);
			float * x2 = vector(1, n+1);
			float * w1 = vector(1, n);
			float * w2 = vector(1, n+1);

			gauher(x1, w1, n);
			gauher(x2, w2, n+1);

			double Vnum = 0.;

			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= n+1; j++) {
					for(int k = 1; k <= n; k++) {
						for(int l = 1; l <= n+1; l++) {
							Vnum += (w1[i] * w2[j] * w1[k] * w2[l]) / (sqrt((x1[i] - x2[j] + x20) * (x1[i] - x2[j] + x20) + (x1[k] - x2[l]) * (x1[k] - x2[l])));				
						}
					}
				}
			}

			double epsilon = fabs((Vdok-Vnum)/Vdok);
			
			fprintf(fp, "%lf %lf\n", x20, epsilon);

			free_vector(R10, 1, 2);
			free_vector(R20, 1, 2);
			free_vector(x1, 1, n);
			free_vector(x2, 1, n+1);
			free_vector(w1, 1, n);
			free_vector(w2, 1, n+1);
		}
		fprintf(fp, "\n\n");
	}

	fclose(fp);
	return 0;
}