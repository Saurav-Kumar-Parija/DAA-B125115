#include <stdio.h>
#include <stdlib.h>

/* Merge two sorted parts */
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

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
}

/* Merge Sort */
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/* Binary Search */
int binarySearch(int arr[], int n, int key)
{
    int left = 0, right = n - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] == key)
            return 1;

        if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return 0;
}

int main()
{
    int n, x;

    printf("Enter size of S1 and S2: ");
    scanf("%d", &n);

    int *S1 = malloc(n * sizeof(int));
    int *S2 = malloc(n * sizeof(int));

    printf("\nEnter elements of S1:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S1[i]);

    printf("\nEnter elements of S2:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S2[i]);

    printf("\nEnter value of x: ");
    scanf("%d", &x);

    /* Sort S2 */
    mergeSort(S2, 0, n - 1);

    printf("\nSorted S2: ");
    for (int i = 0; i < n; i++)
        printf("%d ", S2[i]);

    /* Find a pair */
    int found = 0;

    for (int i = 0; i < n; i++)
    {
        int required = x - S1[i];

        if (binarySearch(S2, n, required))
        {
            printf("\n\nPair found: %d + %d = %d\n",
                   S1[i], required, x);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\n\nNo pair exists whose sum is %d.\n", x);

    free(S1);
    free(S2);

    return 0;
}