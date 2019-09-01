#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define frand() ((double)rand())/(RAND_MAX+1.0)
#define N 1000000

void roznica(double * vec1, double * vec2, double * result, int size);

double iloczynSkalarny(double * vec1, double * vec2, int size);

double momentBezwladnosciMC(double * R_1, double * R_2, char * filename);

int main() {
	double R_11[3] = {-1, -1, -1};
	double R_21[3] = {1, 1, 1};

	double result = momentBezwladnosciMC(R_11, R_21, "result1.dat");
	printf("%lf\n", result);

	double R_12[3] = {1, 1, 1};
	double R_22[3] = {1, 1, -1};
	result = momentBezwladnosciMC(R_12, R_22, "result2.dat");
	printf("%lf\n", result);

	return 0;
}

void roznica(double * vec1, double * vec2, double * result, int size) {
	for(int i = 0; i < size; i++)
		result[i] = vec1[i] - vec2[i];
}

double iloczynSkalarny(double * vec1, double * vec2, int size) {
	double sum = 0;
	for(int i = 0; i < size; i++)
		sum += vec1[i] * vec2[i];
	return sum;
}

double momentBezwladnosciMC(double * R_1, double * R_2, char * filename) {
	srand(0);
	int ro = 1;
	int a = 4;
	
	double R_1i[3];
	double R_21[3];
	double R_i[3];
	double r_i;
	double I = 0;
	double V = a * a * a;
	double tmp = 0;
	double tmp1 = 0;
	double wariancja;
	double odchylenie;
	int theta;
	FILE * fp = fopen(filename, "w");

	for(int i = 1; i <= N; i++) {
		R_i[0] = frand() * 4 - 2; R_i[1] = frand() * 4 - 2; R_i[2] = frand() * 4 - 2;
		roznica(R_1, R_i, R_1i, 3);
		roznica(R_2, R_1, R_21, 3);
		r_i = sqrt((iloczynSkalarny(R_1i, R_1i, 3) * iloczynSkalarny(R_21, R_21, 3) - (iloczynSkalarny(R_1i, R_21, 3) * iloczynSkalarny(R_1i, R_21, 3)))  /  iloczynSkalarny(R_21, R_21, 3));
		
		if(R_i[0] <= 1 && R_i[0] >= -1 && R_i[1] <= 1 && R_i[1] >= -1 && R_i[2] <= 1 && R_i[2] >= -1)
			theta = 1;
		else
			theta = 0;

		tmp = V * ro * r_i * r_i * theta;
		tmp1 += tmp * tmp;
		I += tmp;
		
		wariancja = (tmp1 - ((I * I) / i))/i;
		odchylenie = sqrt(wariancja / i);
		
		if(i%1000 == 0)
			fprintf(fp, "%10d %10lf %10lf\n", i, I/i, odchylenie);

	}

	fclose(fp);

	return I/N;
}