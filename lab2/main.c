#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/ludcmp.c"
#include "/opt/NR/numerical_recipes.c/lubksb.c"

#define N 3

void printMatrix(char * text, float ** matrix, int size) {
	printf("%s", text);
	for(int i = 1; i <= size; i++) {
		for(int j = 1; j <= size; j ++) {
			printf("%12g ", matrix[i][j]);
		}
		printf("\n");
	}
}

void fprintMatrix(FILE * file, char * text, float ** matrix, int size) {
	fprintf(file, "%s", text);
	for(int i = 1; i <= size; i++) {
		for(int j = 1; j <= size; j ++) {
			fprintf(file, "%12g ", matrix[i][j]);
		}
		fprintf(file, "\n");
	}
}


int main(void) {

	FILE * file = fopen("result.dat", "w");

	float ** A  = matrix(1, N, 1, N);
	float ** B = matrix(1, N, 1, N);
	int iterator = 1;

	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j ++) {
			A[i][j] = iterator;
			B[i][j] = iterator;
			iterator++;
		}
	}
	B[1][1] = 1.1;

    printMatrix("Macierz A:\n", A, N);
    fprintMatrix(file, "Macierz A:\n", A, N);
    printMatrix("\nMacierz B:\n", B, N);
    fprintMatrix(file, "\nMacierz B:\n", B, N);

    int * indxA = ivector(1, N);
    int * indxB = ivector(1, N);
    float dA;
    float dB;
    ludcmp(A, N, indxA, &dA);
    ludcmp(B, N, indxB, &dB);
    

	float ** LA  = matrix(1, N, 1, N);
	float ** LB = matrix(1, N, 1, N);
	float ** UA  = matrix(1, N, 1, N);
	float ** UB = matrix(1, N, 1, N);
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j ++) {
			if (i == j) {
				LA[i][j] = 1;
				LB[i][j] = 1;
				UA[i][j] = A[i][j];
				UB[i][j] = B[i][j];
			}
			else if(i < j) {
				LA[i][j] = 0;
				LB[i][j] = 0;
				UA[i][j] = A[i][j];
				UB[i][j] = B[i][j];
			}
			else {
				LA[i][j] = A[i][j];
				LB[i][j] = B[i][j];
				UA[i][j] = 0;
				UB[i][j] = 0;
			}
			iterator++;
		}
	}

    printMatrix("\nMacierz L dla rozkladu macierzy A:\n", LA, N);
    fprintMatrix(file, "\nMacierz L dla rozkladu macierzy A:\n", LA, N);
    printMatrix("\nMacierz U dla rozkladu macierzy A:\n", UA, N);
    fprintMatrix(file, "\nMacierz U dla rozkladu macierzy A:\n", UA, N);

    printMatrix("\nMacierz L dla rozkladu macierzy B:\n", LB, N);
    fprintMatrix(file, "\nMacierz L dla rozkladu macierzy B:\n", LB, N);
    printMatrix("\nMacierz U dla rozkladu macierzy B:\n", UB, N);
    fprintMatrix(file, "\nMacierz U dla rozkladu macierzy B:\n", UB, N);

    float * a1 = vector(1, N);
    float * a2 = vector(1, N);
    float * a3 = vector(1, N);

    float * b1 = vector(1, N);
    float * b2 = vector(1, N);
    float * b3 = vector(1, N);

    a1[1] = 1; a1[2] = 0; a1[3] = 0;
    a2[1] = 0; a2[2] = 1; a2[3] = 0;
    a3[1] = 0; a3[2] = 0; a3[3] = 1;

    b1[1] = 1; b1[2] = 0; b1[3] = 0;
    b2[1] = 0; b2[2] = 1; b2[3] = 0;
    b3[1] = 0; b3[2] = 0; b3[3] = 1;

    lubksb(A, N, indxA, a1);
    lubksb(A, N, indxA, a2);
    lubksb(A, N, indxA, a3);
    lubksb(B, N, indxB, b1);
    lubksb(B, N, indxB, b2);
    lubksb(B, N, indxB, b3);

    float ** A_inverse = matrix(1, N, 1, N);
    float ** B_inverse = matrix(1, N, 1, N);

    for(int i = 1; i <= N; i++) {
        A_inverse[i][1] = a1[i];
        A_inverse[i][2] = a2[i];
        A_inverse[i][3] = a3[i];
        B_inverse[i][1] = b1[i];
        B_inverse[i][2] = b2[i];
        B_inverse[i][3] = b3[i];
    }

    printMatrix("\nMacierz A^-1:\n", A_inverse, N);
    fprintMatrix(file, "\nMacierz A^-1:\n", A_inverse, N);
    printMatrix("\nMacierz B^-1:\n", B_inverse, N);
	fprintMatrix(file, "\nMacierz B^-1:\n", B_inverse, N);

  iterator = 1;

    for(int i = 1; i <= N; i++) {
  		for(int j = 1; j <= N; j ++) {
  			A[i][j] = iterator;
  			B[i][j] = iterator;
  			iterator++;
  		}
  	}
  	B[1][1] = 1.1;

    float maxA = 0, maxB = 0, maxA_inverse = 0, maxB_inverse = 0;

    for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j ++) {
			if(fabs(A[i][j]) > maxA)
				maxA = fabs(A[i][j]);
		
			if(fabs(B[i][j]) > maxB)
				maxB = fabs(B[i][j]);

			if(fabs(A_inverse[i][j]) > maxA_inverse)
				maxA_inverse= fabs(A_inverse[i][j]);

			if(fabs(B_inverse[i][j]) > maxB_inverse)
				maxB_inverse= fabs(B_inverse[i][j]);
		}
	}

	float kappaA = maxA * maxA_inverse;
	float kappaB = maxB * maxB_inverse;
	printf("\n||A|| = %g\n||A^-1|| = %f = %g\nKappaA = %f = %g\n", maxA, maxA_inverse, maxA_inverse, kappaA, kappaA);
	fprintf(file, "\n||A|| = %g\n||A^-1|| = %f = %g\nKappaA = %f = %g\n", maxA, maxA_inverse, maxA_inverse, kappaA, kappaA);
	printf("\n||B|| = %g\n||B^-1|| = %f\nKappaB = %f\n", maxB, maxB_inverse, kappaB);	
	fprintf(file, "\n||B|| = %g\n||B^-1|| = %f\nKappaB = %f\n", maxB, maxB_inverse, kappaB);		

	 iterator = 1;

	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j ++) {
			A[i][j] = iterator;
			B[i][j] = iterator;
			iterator++;
		}
	}
	B[1][1] = 1.1;

	float ** A_product = matrix(1, N, 1, N);
	float ** B_product = matrix(1, N, 1, N);
	
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			A_product[i][j] = B_product[i][j] = 0;

	int k;
	float sumA = 0, sumB = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sumA = sumB = 0;

			for (int k = 1; k <= N; k++) {
				sumA = sumA + A[i][k] * A_inverse[k][j];
				sumB = sumB + B[i][k] * B_inverse[k][j];
			}

			A_product[i][j] = sumA;
			B_product[i][j] = sumB;
		}
	}

	printMatrix("\nIloczyn A x A^-1:\n", A_product, N); 
	fprintMatrix(file, "\nIloczyn A x A^-1:\n", A_product, N); 
	printMatrix("\nIloczyn B x B^-1:\n", B_product, N);
	fprintMatrix(file, "\nIloczyn B x B^-1:\n", B_product, N);

	fclose(file);

    free_matrix(A, 1, N, 1, N);
    free_matrix(B, 1, N, 1, N);
    free_matrix(LA, 1, N, 1, N);
    free_matrix(LB, 1, N, 1, N);
    free_matrix(UA, 1, N, 1, N);
    free_matrix(UB, 1, N, 1, N);
    free_matrix(A_inverse, 1, N, 1, N);
    free_matrix(B_inverse, 1, N, 1, N);
    free_matrix(A_product, 1, N, 1, N);
    free_matrix(B_product, 1, N, 1, N);
    free_vector(a1, 1, N);
    free_vector(a2, 1, N);
    free_vector(a3, 1, N);
    free_vector(b1, 1, N);
    free_vector(b2, 1, N);
    free_vector(b3, 1, N);
    free_ivector(indxA, 1, N);
    free_ivector(indxB, 1, N);
	return 0;
}
