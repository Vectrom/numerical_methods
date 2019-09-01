#include <stdio.h>
#include <math.h>

double g(double x, double y);
double dgdx(double x, double y);
double dgdy(double x, double y);
void MatVec(double (*matrix)[2], double * vector, double * result, int size);
void findMinimum(double omega, double x0, double y0, double (*matrix)[2]);

int main() {
    double A[2][2];
    A[0][0] = 2.; A[0][1] = 1;
    A[1][0] = 1.; A[1][1] = 2;

    double b[2] = {-4. , -4.};
    
    double A_odw[2][2];
    double wsp = 1. / (A[0][0]*A[1][1] - A[0][1]*A[1][0]);
    A_odw[0][0] = wsp * A[1][1];
    A_odw[0][1] =  -wsp * A[0][1];
    A_odw[1][0] =  -wsp * A[1][0];
    A_odw[1][1] = wsp * A[0][0];

    double r_min[2];
    MatVec(A_odw, b, r_min, 2);
    r_min[0] = -r_min[0];
    r_min[1] = -r_min[1]; 

    printf("r_min = (%g, %g)\n\n", r_min[0], r_min[1]);

    findMinimum(1, 0, 0, A_odw);
    findMinimum(1, 10, -10, A_odw);
    findMinimum(1, 100, 100, A_odw);
    findMinimum(1, 500, 500, A_odw);

    printf("\n");

    findMinimum(0.1, 10, 10, A_odw);
    findMinimum(0.4, 10, 10, A_odw);
    findMinimum(0.7, 10, 10, A_odw);

    return 0;
}

double g(double x, double y) {
    return x*x - 4*x + y*y - 4*y + x*y;
}

double dgdx(double x, double y) {
    double dx = 0.001;
    return (g(x+dx, y) - g(x-dx, y)) / (2*dx);
}

double dgdy(double x, double y) {
    double dy = 0.001;
    return (g(x, y+dy) - g(x, y-dy)) / (2*dy);
}

void MatVec(double (*matrix)[2], double * vector, double * result, int size) {
    for (int i = 0; i < size; i++) {
        double tmp = 0.0;
        for (int j = 0; j < size; j++) 
            tmp += matrix[i][j] * vector[j];
        result[i] = tmp;
    }
}

void findMinimum(double omega, double x0, double y0, double (*matrix)[2]) {
    double r_n[2];
    double r[2] = {x0, y0};
    int iterator = 0;
    while (1) {
        iterator++;
        double tmp1[2] = {dgdx(r[0], r[1]), dgdy(r[0], r[1])};
        double tmp2[2];

        MatVec(matrix, tmp1, tmp2, 2);

        r_n[0] = r[0] - omega * tmp2[0];
        r_n[1] = r[1] - omega * tmp2[1];

        if (sqrt((r_n[0] - r[0]) * (r_n[0] - r[0]) + (r_n[1] - r[1]) * (r_n[1] - r[1])) < 1e-6) {
            break;
        }

        r[0] = r_n[0];
        r[1] = r_n[1];
    }
    printf("punkt = (%.0lf, %.0lf), omega = %.1lf, liczba iteracji = %d, x_min = %g, y_min = %g\n", x0, y0, omega, iterator, r_n[0], r_n[1]);
}