#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void reverse(int p[], int left, int right, long long *cost)
{
    int temp;
    if (left > right)
        return;

    *cost += right - left + 1;
    while (left < right) {
        temp = p[left];
        p[left] = p[right];
        p[right] = temp;
        left++;
        right--;
    }
}

void rotate(int p[], int left, int mid, int right, long long *cost)
{
    if (left >= mid || mid >= right)
        return;

    reverse(p, left, mid - 1, cost);
    reverse(p, mid, right - 1, cost);
    reverse(p, left, right - 1, cost);
}

void stablePartition(int p[], int left, int right, int bit,long long *cost)
{
    int mid;
    int i, j;
    if (right - left <= 1)
        return;

    mid = (left + right) / 2;
    stablePartition(p, left, mid, bit, cost);
    stablePartition(p, mid, right, bit, cost);
    i = left;
    while (i < mid && ((p[i] >> bit) & 1) == 0)
        i++;

    j = mid;
    while (j < right && ((p[j] >> bit) & 1) == 0)
        j++;

    rotate(p, i, mid, j, cost);
}

void radixSort(int p[], int n, long long *cost)
{
    int maxValue = n;
    int bits = 0;
    int i;
    while ((1 << bits) <= maxValue)
        bits++;

    for (i = bits - 1; i >= 0; i--)
        stablePartition(p, 0, n, i, cost);
}

int isSorted(int p[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        if (p[i] != i + 1)
            return 0;

    return 1;
}

int main()
{
    int n, i;
    int *p;
    long long cost = 0;
    clock_t start, end;
    printf("Enter n: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid value of n.\n");
        return 1;
    }
    p = malloc(n * sizeof(int));
    if (p == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Enter the permutation:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);

    start = clock();
    radixSort(p, n, &cost);
    end = clock();

    printf("\nSorted permutation:\n");
    for (i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");
    printf("Sorted: %s\n", isSorted(p, n) ? "Yes" : "No");
    printf("Total reversal cost: %lld\n", cost);
    printf("Execution time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    free(p);
    
    return 0;
}