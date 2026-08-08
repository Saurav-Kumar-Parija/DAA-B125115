//merge k sorted arrays
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int *data;
    int size;
} Array;

/* Merge two sorted arrays */
Array merge(Array A, Array B)
{
    Array C;
    C.size = A.size + B.size;
    C.data = (int *)malloc(C.size * sizeof(int));

    int i = 0, j = 0, k = 0;

    while (i < A.size && j < B.size)
    {
        if (A.data[i] <= B.data[j])
            C.data[k++] = A.data[i++];
        else
            C.data[k++] = B.data[j++];
    }

    while (i < A.size)
        C.data[k++] = A.data[i++];

    while (j < B.size)
        C.data[k++] = B.data[j++];

    return C;
}

/* Generate k sorted arrays */
Array *generateArrays(int k, int n)
{
    Array *arr = (Array *)malloc(k * sizeof(Array));

    for (int i = 0; i < k; i++)
    {
        arr[i].size = n;
        arr[i].data = (int *)malloc(n * sizeof(int));

        int value = i * 100000;

        for (int j = 0; j < n; j++)
            arr[i].data[j] = value + j;
    }

    return arr;
}

/* Free arrays */
void freeArrays(Array *arr, int k)
{
    for (int i = 0; i < k; i++)
        free(arr[i].data);

    free(arr);
}

/* ---------------- METHOD 1 ---------------- */

Array method1(Array *input, int k)
{
    Array result = merge(input[0], input[1]);

    for (int i = 2; i < k; i++)
    {
        Array temp = merge(result, input[i]);

        free(result.data);

        result = temp;
    }

    return result;
}

/* ---------------- METHOD 2 ---------------- */

Array method2(Array *input, int k)
{
    Array *current = (Array *)malloc(k * sizeof(Array));

    for (int i = 0; i < k; i++)
        current[i] = input[i];

    int currentSize = k;

    while (currentSize > 1)
    {
        int newSize = 0;

        for (int i = 0; i < currentSize; i += 2)
        {
            if (i + 1 < currentSize)
            {
                current[newSize++] = merge(current[i], current[i + 1]);
            }
            else
            {
                current[newSize++] = current[i];
            }
        }

        currentSize = newSize;
    }

    Array result = current[0];

    free(current);

    return result;
}

int main()
{
    FILE *fp = fopen("data.dat", "w");

    if (fp == NULL)
    {
        printf("Unable to create data file.\n");
        return 1;
    }

    int n = 5000;     // Elements in each array

    printf("Comparing Method 1 and Method 2\n");
    printf("--------------------------------------------\n");
    printf("k\tMethod1\t\tMethod2\n");

    for(int k = 2; k <= 64; k *= 2)
    {
        /* ---------- Method 1 ---------- */

        Array *arrays1 = generateArrays(k, n);

        clock_t start = clock();

        Array result1 = method1(arrays1, k);

        clock_t end = clock();

        double t1 = (double)(end-start)/CLOCKS_PER_SEC;

        free(result1.data);
        freeArrays(arrays1, k);

        /* ---------- Method 2 ---------- */

        Array *arrays2 = generateArrays(k, n);

        start = clock();

        Array result2 = method2(arrays2, k);

        end = clock();

        double t2 = (double)(end-start)/CLOCKS_PER_SEC;

        free(result2.data);
        freeArrays(arrays2, k);

        printf("%d\t%.6lf\t%.6lf\n", k, t1, t2);

        fprintf(fp,"%d %lf %lf\n", k, t1, t2);

        
        
        if (t2 < t1)
        printf("Method 2 is faster.\n");
        
        else if(t2>t1)
        printf("Method 1 is faster.\n");

        else
        printf("Both have equal speed.\n");
    }
    
    fclose(fp);

    /* ---------- GNUPLOT ---------- */

    FILE *gp = popen("gnuplot -persistent", "w");

    if(gp == NULL)
    {
        printf("Gnuplot not found.\n");
        return 1;
    }

    fprintf(gp, "set title 'Merging k Sorted Arrays'\n");
    fprintf(gp, "set xlabel 'Number of Arrays (k)'\n");
    fprintf(gp, "set ylabel 'Execution Time (seconds)'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set style data linespoints\n");

    fprintf(gp,
        "plot 'data.dat' using 1:2 title 'Method 1 (Sequential Merge)' lw 2 lc rgb 'blue',\\\n");

    fprintf(gp,
        "'data.dat' using 1:3 title 'Method 2 (Pairwise Merge)' lw 2 lc rgb 'red'\n");

    fflush(gp);
    pclose(gp);

    return 0;
}