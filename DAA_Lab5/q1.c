#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}

int quickselect(int a[], int low, int high, int k)
{
    while (low <= high)
    {
        int pivotIndex = partition(a, low, high);

        if (pivotIndex == k)
            return a[pivotIndex];

        else if (k < pivotIndex)
            high = pivotIndex - 1;

        else
            low = pivotIndex + 1;
    }

    return -1;
}

int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int median;

    if (n % 2 != 0)
    {
        int k = n / 2;
        median = quickselect(a, 0, n - 1, k);

        printf("Median = %d\n", median);
    }
    else
    {
        int k1 = n / 2 - 1;
        int k2 = n / 2;

        int x = quickselect(a, 0, n - 1, k1);
        int y = quickselect(a, 0, n - 1, k2);

        printf("Middle elements = %d and %d\n", x, y);
        printf("Median = %.2f\n", (x + y) / 2.0);
    }

    free(a);

    return 0;
}