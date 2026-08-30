#include <stdio.h>
#include <stdlib.h>

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
    int n, k;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter the value of K: ");
    scanf("%d", &k);

    if (k < 1 || k > n)
    {
        printf("Invalid value of K.\n");
        free(a);
        return 0;
    }

    int index = k - 1;

    int result = quickselect(a, 0, n - 1, index);

    printf("%dth smallest element = %d\n", k, result);

    free(a);

    return 0;
}