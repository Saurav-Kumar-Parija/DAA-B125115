#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 100

void addMatrix(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiplyMatrix(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int isZeroMatrix(int A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != 0)
                return 0;

    return 1;
}

int isSymmetric(int A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (A[i][j] != A[j][i])
                return 0;

    return 1;
}

double determinant(int A[MAX][MAX], int n)
{
    double temp[MAX][MAX];
    double det = 1.0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][j] = A[i][j];

    for (int i = 0; i < n; i++) {
        int pivot = i;

        for (int j = i + 1; j < n; j++)
            if (fabs(temp[j][i]) > fabs(temp[pivot][i]))
                pivot = j;

        if (fabs(temp[pivot][i]) < 1e-9)
            return 0.0;

        if (pivot != i) {
            for (int j = 0; j < n; j++) {
                double x = temp[i][j];
                temp[i][j] = temp[pivot][j];
                temp[pivot][j] = x;
            }
            det = -det;
        }

        det *= temp[i][i];
        for (int j = i + 1; j < n; j++) {
            double factor = temp[j][i] / temp[i][i];

            for (int k = i + 1; k < n; k++)
                temp[j][k] -= factor * temp[i][k];
        }
    }

    return det;
}

void transpose(int A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
}

void dominantEigen(int A[MAX][MAX], int n, double eigenvector[MAX],
                   double *eigenvalue, int iterations)
{
    double next[MAX];
    for (int i = 0; i < n; i++)
        eigenvector[i] = 1.0;

    for (int iter = 0; iter < iterations; iter++) {
        double maxValue = 0.0;

        for (int i = 0; i < n; i++) {
            next[i] = 0.0;

            for (int j = 0; j < n; j++)
                next[i] += A[i][j] * eigenvector[j];

            if (fabs(next[i]) > maxValue)
                maxValue = fabs(next[i]);
        }
        for (int i = 0; i < n; i++)
            eigenvector[i] = next[i] / maxValue;
    }

    double Av[MAX];
    for (int i = 0; i < n; i++) {
        Av[i] = 0.0;

        for (int j = 0; j < n; j++)
            Av[i] += A[i][j] * eigenvector[j];
    }

    *eigenvalue = 0.0;
    for (int i = 0; i < n; i++)
        if (fabs(eigenvector[i]) > 1e-9)
            *eigenvalue = Av[i] / eigenvector[i];
}

void displayMatrix(int A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}

int main()
{
    int n;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    double eigenvector[MAX], eigenvalue;
    int iterations = 100;

    printf("Enter the order of square matrices: ");
    scanf("%d", &n);
    printf("\nEnter elements of Matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("\nEnter elements of Matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    clock_t start, end;
    start = clock();
    addMatrix(A, B, C, n);
    end = clock();

    printf("\nMatrix Addition:\n");
    displayMatrix(C, n);
    printf("Time: %f seconds\n",(double)(end - start) / CLOCKS_PER_SEC);
    start = clock();
    multiplyMatrix(A, B, C, n);
    end = clock();

    printf("\nMatrix Multiplication:\n");
    displayMatrix(C, n);
    printf("Time: %f seconds\n",(double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    int zero = isZeroMatrix(A, n);
    end = clock();

    printf("\nZero Matrix: %s\n", zero ? "Yes" : "No");
    printf("Time: %f seconds\n",(double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    int symmetric = isSymmetric(A, n);
    end = clock();

    printf("\nSymmetric Matrix: %s\n", symmetric ? "Yes" : "No");
    printf("Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    double det = determinant(A, n);
    end = clock();

    printf("\nDeterminant: %.2lf\n", det);
    printf("Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    int T[MAX][MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            T[i][j] = A[i][j];

    start = clock();
    transpose(T, n);
    end = clock();

    printf("\nTranspose of Matrix A:\n");
    displayMatrix(T, n);
    printf("Time: %f seconds\n",(double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    dominantEigen(A, n, eigenvector, &eigenvalue, iterations);
    end = clock();

    printf("\nDominant Eigenvalue: %.6lf\n", eigenvalue);
    printf("Eigenvector:\n");
    for (int i = 0; i < n; i++)
        printf("%.6lf ", eigenvector[i]);

    printf("\nTime: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}