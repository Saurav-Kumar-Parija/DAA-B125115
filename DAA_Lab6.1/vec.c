#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double real;
    double imag;
} Complex;

Complex add(Complex a, Complex b)
{
    Complex c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
    return c;
}

Complex subtract(Complex a, Complex b)
{
    Complex c;
    c.real = a.real - b.real;
    c.imag = a.imag - b.imag;
    return c;
}

Complex multiply(Complex a, Complex b)
{
    Complex c;
    c.real = a.real * b.real - a.imag * b.imag;
    c.imag = a.real * b.imag + a.imag * b.real;
    return c;
}

void fft(Complex a[], int n, int invert)
{
    int i, j, k;
    Complex temp, u, v;
    double angle, wReal, wImag, nextWReal, nextWImag;
    for (i = 1, j = 0; i < n; i++) {
        int bit;
        for (bit = n >> 1; j & bit; bit >>= 1)
            j ^= bit;

        j ^= bit;

        if (i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    for (int len = 2; len <= n; len <<= 1) {
        angle = 2 * PI / len * (invert ? 1 : -1);
        wReal = cos(angle);
        wImag = sin(angle);
        for (i = 0; i < n; i += len) {
            double currentReal = 1.0;
            double currentImag = 0.0;
            for (j = 0; j < len / 2; j++) {
                u = a[i + j];
                v = multiply(a[i + j + len / 2], (Complex){currentReal, currentImag});
                a[i + j] = add(u, v);
                a[i + j + len / 2] = subtract(u, v);
                nextWReal = currentReal * wReal - currentImag * wImag;
                nextWImag = currentReal * wImag + currentImag * wReal;
                currentReal = nextWReal;
                currentImag = nextWImag;
            }
        }
    }

    if (invert) {
        for (i = 0; i < n; i++) {
            a[i].real /= n;
            a[i].imag /= n;
        }
    }
}

int nextPowerOfTwo(int size)
{
    int n = 1;
    while (n < size)
        n <<= 1;

    return n;
}

void convolution(double A[], int m, double B[], int n,double C[])
{
    int i;
    int size = m + n - 1;
    int N = nextPowerOfTwo(size);

    Complex *FA = calloc(N, sizeof(Complex));
    Complex *FB = calloc(N, sizeof(Complex));

    if (FA == NULL || FB == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (i = 0; i < m; i++)
        FA[i].real = A[i];

    for (i = 0; i < n; i++)
        FB[i].real = B[i];

    fft(FA, N, 0);
    fft(FB, N, 0);
    for (i = 0; i < N; i++)
        FA[i] = multiply(FA[i], FB[i]);

    fft(FA, N, 1);
    for (i = 0; i < size; i++)
        C[i] = FA[i].real;

    free(FA);
    free(FB);
}

int main()
{
    int m, n, i;
    double *A, *B, *C;
    printf("Enter size of vector A: ");
    scanf("%d", &m);
    printf("Enter size of vector B: ");
    scanf("%d", &n);
    if (n < m) {
        printf("Condition n >= m is required.\n");
        return 1;
    }
    A = malloc(m * sizeof(double));
    B = malloc(n * sizeof(double));
    C = malloc((m + n - 1) * sizeof(double));
    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Enter elements of A:\n");
    for (i = 0; i < m; i++)
        scanf("%lf", &A[i]);

    printf("Enter elements of B:\n");
    for (i = 0; i < n; i++)
        scanf("%lf", &B[i]);

    convolution(A, m, B, n, C);
    printf("\nConvolution vector C:\n");
    for (i = 0; i < m + n - 1; i++)
        printf("%.2lf ", C[i]);

    printf("\n");
    free(A);
    free(B);
    free(C);

    return 0;
}