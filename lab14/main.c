#include <math.h>
#include <stdio.h>

#define N 2000
#define K 10

double gen_1();
double gen_2();
double gen_3();
void gestosc(char * nj_file_name, char * gj_file_name, int n);

int main() {
	FILE * fp_gen1 = fopen("generator1.dat", "w");
	FILE * fp_gen2 = fopen("generator2.dat", "w");
	FILE * fp_gen3 = fopen("generator3.dat", "w");

	double u1_results[N];
	double u2_results[N];
	double u3_results[N];

	for(int i = 0; i < N; i++) {
		u1_results[i] = gen_1();
		u2_results[i] = gen_2();
		u3_results[i] = gen_3();
	}

	for (int i = 0; i < N - 3; i++) {
		fprintf(fp_gen1, "%15g %15g %15g %15g\n", u1_results[i], u1_results[i+1], u1_results[i+2], u1_results[i+3]);
		fprintf(fp_gen2, "%15g %15g %15g %15g\n", u2_results[i], u2_results[i+1], u2_results[i+2], u2_results[i+3]);
		fprintf(fp_gen3, "%15g %15g %15g %15g\n", u3_results[i], u3_results[i+1], u3_results[i+2], u3_results[i+3]);
	}

	fprintf(fp_gen1, "%15g %15g %15g\n", u1_results[N-3], u1_results[N-2], u1_results[N-1]);
	fprintf(fp_gen2, "%15g %15g %15g\n", u2_results[N-3], u2_results[N-2], u2_results[N-1]);
	fprintf(fp_gen3, "%15g %15g %15g\n", u3_results[N-3], u3_results[N-2], u3_results[N-1]);
	fprintf(fp_gen1, "%15g %15g\n", u1_results[N-2], u1_results[N-1]);
	fprintf(fp_gen2, "%15g %15g\n", u2_results[N-2], u2_results[N-1]);
	fprintf(fp_gen3, "%15g %15g\n", u3_results[N-2], u3_results[N-1]);

	fclose(fp_gen1);
	fclose(fp_gen2);
	fclose(fp_gen3);

	///////////////////////////////////////////////////////////////////////////////////////////////

	FILE * fp_sfera = fopen("sfera.dat", "w");
	FILE * fp_kula = fopen("kula.dat", "w");

	double sfera[N][3];
	double kula[N][3];

	for (int i = 0; i < N; i++) {
		double u1 = gen_3();
		double u2 = gen_3();
		double u3 = gen_3();
		double u4 = gen_3();

		sfera[i][0] = sqrt(-2 * log(1 - u1)) * cos(2 * M_PI * u2);
		sfera[i][1] = sqrt(-2 * log(1 - u1)) * sin(2 * M_PI * u2);
		sfera[i][2] = sqrt(-2 * log(1 - u3)) * cos(2 * M_PI * u4);

		double norm = sqrt(pow(sfera[i][0], 2) + pow(sfera[i][1], 2) + pow(sfera[i][2], 2));

		sfera[i][0] /= norm; 
		sfera[i][1] /= norm; 
		sfera[i][2] /= norm; 

		fprintf(fp_sfera, "%15g %15g %15g\n", sfera[i][0],  sfera[i][1],  sfera[i][2]);

		double ui = gen_3();
		double si = pow(ui, 1.0/3.0);
		kula[i][0] = sfera[i][0] * si;
		kula[i][1] = sfera[i][1] * si;
		kula[i][2] = sfera[i][2] * si;	
		fprintf(fp_kula, "%15g %15g %15g\n", kula[i][0],  kula[i][1],  kula[i][2]);
 
	}

	fclose(fp_sfera);
	fclose(fp_kula);

	gestosc("nj1.dat", "gj1.dat", 2000);
	gestosc("nj2.dat", "gj2.dat", pow(10, 4));
	gestosc("nj3.dat", "gj3.dat", pow(10, 7));

	return 0;
}


double gen_1() {
	static long int x  = 10;
	int a = 17;
	long int m = pow(2, 13) - 1;
	x = (a * x) % m;
	return x /(m + 1.0);
}

double gen_2() {
	static long int x  = 10;
	int a = 85;
	long int m = pow(2, 13) - 1;
	x = (a * x) % m;
	return x /(m + 1.0);
}

double gen_3() {
	static long int x0  = 10;
	static long int x1  = 10;
	static long int x2  = 10;	
	int a0 = 1176;
	int a1 = 1476;
	int a2 = 1776;
	long int m = pow(2, 32) - 5;
	long int tmp = (a0 * x0 + a1 * x1 + a2 * x2) % m;
	x2 = x1;
	x1 = x0;
	x0 = tmp;
	return x0 /(m+1.0);
}

void gestosc(char * nj_file_name, char * gj_file_name, int n) {
	FILE * nj_file = fopen(nj_file_name, "w"); 
	FILE * gj_file = fopen(gj_file_name, "w"); 

	double delta = 1.0 / K;
    double nj[K] = {0};

    double kula_x, kula_y, kula_z;

    for (int i = 0; i < n; i++) {
    	double u1 = gen_3();
		double u2 = gen_3();
		double u3 = gen_3();
		double u4 = gen_3();

		double x = sqrt(-2 * log(1 - u1)) * cos(2 * M_PI * u2);
		double y = sqrt(-2 * log(1 - u1)) * sin(2 * M_PI * u2);
		double z = sqrt(-2 * log(1 - u3)) * cos(2 * M_PI * u4);

		double norm = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

		x /= norm; 
		y /= norm; 
		z /= norm;

		double ui = gen_3();
		double si = pow(ui, 1.0/3.0);
		kula_x = x * si;
		kula_y = y * si;
		kula_z = z * si;	

		norm = sqrt(pow(kula_x, 2) + pow(kula_y, 2) + pow(kula_z, 2));

		int j = (int)(norm / delta);
		nj[j]++;
    }

    for(int i = 0; i < K; i++) {
    	double Rj = delta * (i+1);
        double Rj1 = delta * (i);
        double Vj = (4.0 / 3.0) * M_PI * pow(Rj, 3);
        double Vj1 = (4.0 / 3.0) * M_PI * pow(Rj1, 3);
        double gj = nj[i] / (Vj - Vj1);
        fprintf(nj_file, "%15d %15g\n", i, nj[i]);
        fprintf(gj_file, "%15d %15g\n", i, gj);
    }

    fclose(nj_file);
    fclose(gj_file);
}