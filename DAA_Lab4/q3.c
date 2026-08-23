#include <stdio.h>
#include <stdlib.h>

/* Merge two sorted portions */
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

/* Merge Sort */
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/* Binary Search in a specified range */
int binarySearch(int arr[], int left, int right, long long key)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

/*
    Recursively select k-1 elements.

    Once k-1 elements have been selected,
    binary search is used for the final element.
*/
int findKSum(int S[], int n, int k, int T,
            int start, int depth, long long sum,
            int selected[])
{
    /* k-1 elements have been selected */
    if (depth == k - 1)
    {
        long long required = (long long)T - sum;

        /*
           Search only after the last selected index.
           This guarantees that the same element is
           not used twice.
        */
        int pos = binarySearch(
            S,
            start,
            n - 1,
            required
        );

        if (pos != -1)
        {
            selected[depth] = S[pos];

            return 1;
        }

        return 0;
    }

    /*
       Select the next element.
    */
    for (int i = start; i <= n - (k - depth); i++)
    {
        selected[depth] = S[i];

        if (findKSum(
                S,
                n,
                k,
                T,
                i + 1,
                depth + 1,
                sum + S[i],
                selected))
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int n, k, T;

    printf("Enter number of elements (n): ");
    scanf("%d", &n);

    int *S = malloc(n * sizeof(int));

    if (S == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &S[i]);

    printf("Enter value of k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    if (k <= 0 || k > n)
    {
        printf("Invalid value of k.\n");
        free(S);
        return 1;
    }

    /* Sort the set */
    mergeSort(S, 0, n - 1);

    printf("\nSorted set: ");

    for (int i = 0; i < n; i++)
        printf("%d ", S[i]);

    printf("\n");

    int *selected = malloc(k * sizeof(int));

    if (selected == NULL)
    {
        printf("Memory allocation failed.\n");
        free(S);
        return 1;
    }

    /* Find k elements whose sum is T */
    int found = findKSum(
        S,
        n,
        k,
        T,
        0,
        0,
        0,
        selected
    );

    if (found)
    {
        printf("\n%d elements found whose sum is %d:\n",
               k, T);

        for (int i = 0; i < k; i++)
            printf("%d ", selected[i]);

        printf("\n");
    }
    else
    {
        printf("\nNo %d elements exist whose sum is %d.\n",
               k, T);
    }

    free(selected);
    free(S);

    return 0;
}