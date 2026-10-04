#include <stdio.h>
#include <stdlib.h>

void findLIS(int A[], int n)
{
    int *dp = (int *)malloc(n * sizeof(int));
    int *parent = (int *)malloc(n * sizeof(int));

    if (dp == NULL || parent == NULL)
    {
        free(dp);
        free(parent);
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        parent[i] = -1;
    }

    int maxLength = 1;
    int lastIndex = 0;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i] && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }

        if (dp[i] > maxLength)
        {
            maxLength = dp[i];
            lastIndex = i;
        }
    }

    int *lis = (int *)malloc(maxLength * sizeof(int));

    if (lis == NULL)
    {
        free(dp);
        free(parent);
        printf("Memory allocation failed.\n");
        return;
    }

    int index = maxLength - 1;
    int current = lastIndex;

    while (current != -1)
    {
        lis[index] = A[current];
        index--;
        current = parent[current];
    }

    printf("Length of LIS: %d\n", maxLength);

    printf("Longest Increasing Subsequence: ");

    for (int i = 0; i < maxLength; i++)
        printf("%d ", lis[i]);

    printf("\n");

    free(lis);
    free(dp);
    free(parent);
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *A = (int *)malloc(n * sizeof(int));

    if (A == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter array elements: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    findLIS(A, n);

    free(A);

    return 0;
}