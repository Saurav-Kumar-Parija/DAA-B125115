#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Allocate a square matrix 
int **allocateMatrix(int n)
{
    int **A = (int **)malloc(n * sizeof(int *));

    if (A == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        A[i] = (int *)malloc(n * sizeof(int));

        if (A[i] == NULL)
        {
            printf("Memory allocation failed.\n");

            for (int j = 0; j < i; j++)
                free(A[j]);

            free(A);
            exit(1);
        }
    }
    return A;
}

// Free a matrix 
void freeMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
        free(A[i]);

    free(A);
}

// Add two matrices 
void addMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Subtract two matrices 
void subtractMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen's Matrix Multiplication 
void strassen(int **A, int **B, int **C, int n)
{
    /* Base case */
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    //Allocate submatrices 
    int **A11 = allocateMatrix(k);
    int **A12 = allocateMatrix(k);
    int **A21 = allocateMatrix(k);
    int **A22 = allocateMatrix(k);

    int **B11 = allocateMatrix(k);
    int **B12 = allocateMatrix(k);
    int **B21 = allocateMatrix(k);
    int **B22 = allocateMatrix(k);

    int **M1 = allocateMatrix(k);
    int **M2 = allocateMatrix(k);
    int **M3 = allocateMatrix(k);
    int **M4 = allocateMatrix(k);
    int **M5 = allocateMatrix(k);
    int **M6 = allocateMatrix(k);
    int **M7 = allocateMatrix(k);

    int **T1 = allocateMatrix(k);
    int **T2 = allocateMatrix(k);

    // Divide A and B into four submatrices 
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    
    //M1 = (A11 + A22)(B11 + B22)
    
    addMatrix(A11, A22, T1, k);
    addMatrix(B11, B22, T2, k);
    strassen(T1, T2, M1, k);

    
    //M2 = (A21 + A22)B11
    
    addMatrix(A21, A22, T1, k);
    strassen(T1, B11, M2, k);

    
    //M3 = A11(B12 - B22)
    
    subtractMatrix(B12, B22, T2, k);
    strassen(A11, T2, M3, k);

    
    //M4 = A22(B21 - B11)
    
    subtractMatrix(B21, B11, T2, k);
    strassen(A22, T2, M4, k);

   
    //M5 = (A11 + A12)B22
    
    addMatrix(A11, A12, T1, k);
    strassen(T1, B22, M5, k);

    
    //M6 = (A21 - A11)(B11 + B12)
    
    subtractMatrix(A21, A11, T1, k);
    addMatrix(B11, B12, T2, k);
    strassen(T1, T2, M6, k);

    
    //M7 = (A12 - A22)(B21 + B22)
    
    subtractMatrix(A12, A22, T1, k);
    addMatrix(B21, B22, T2, k);
    strassen(T1, T2, M7, k);

    //Construct result matrix C 

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            // C11 = M1 + M4 - M5 + M7 //
            C[i][j] =
                M1[i][j] + M4[i][j]
                - M5[i][j] + M7[i][j];

            //C12 = M3 + M5 
            C[i][j + k] =
                M3[i][j] + M5[i][j];

            // C21 = M2 + M4 
            C[i + k][j] =
                M2[i][j] + M4[i][j];

            // C22 = M1 - M2 + M3 + M6 
            C[i + k][j + k] =
                M1[i][j] - M2[i][j]
                + M3[i][j] + M6[i][j];
        }
    }

    // Free all dynamically allocated matrices 

    freeMatrix(A11, k);
    freeMatrix(A12, k);
    freeMatrix(A21, k);
    freeMatrix(A22, k);

    freeMatrix(B11, k);
    freeMatrix(B12, k);
    freeMatrix(B21, k);
    freeMatrix(B22, k);

    freeMatrix(M1, k);
    freeMatrix(M2, k);
    freeMatrix(M3, k);
    freeMatrix(M4, k);
    freeMatrix(M5, k);
    freeMatrix(M6, k);
    freeMatrix(M7, k);

    freeMatrix(T1, k);
    freeMatrix(T2, k);
}

// Display matrix 
void displayMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%6d", A[i][j]);

        printf("\n");
    }
}

int main()
{
    int n;

    printf("Enter size of square matrix (power of 2): ");
    scanf("%d", &n);

    // Check valid size 
    if (n <= 0 || (n & (n - 1)) != 0)
    {
        printf("Matrix size must be a positive power of 2.\n");
        printf("Example: 2, 4, 8, 16, 32...\n");
        return 1;
    }

    // Allocate matrices 
    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    // Input Matrix A 
    printf("\nEnter elements of Matrix A:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    // Input Matrix B 
    printf("\nEnter elements of Matrix B:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    // Display input matrices 
    printf("\nMatrix A:\n");
    displayMatrix(A, n);

    printf("\nMatrix B:\n");
    displayMatrix(B, n);

    // Perform Strassen multiplication 
    clock_t start = clock();

    strassen(A, B, C, n);

    clock_t end = clock();

    double timeTaken =
        (double)(end - start) / CLOCKS_PER_SEC;

    //Display result 
    printf("\nResult Matrix C = A x B:\n");
    displayMatrix(C, n);

    printf("\nExecution Time: %.6f seconds\n", timeTaken);

    //Free memory 
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}