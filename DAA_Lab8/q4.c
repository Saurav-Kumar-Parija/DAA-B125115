#include <stdio.h>
#include <stdlib.h>

void findMaximumSumIS(int A[], int n) {
    int *dp = malloc(n * sizeof(int));
    int *parent = malloc(n * sizeof(int));

    if (dp == NULL || parent == NULL) {
        printf("Memory allocation failed.\n");
        free(dp);
        free(parent);
        return;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = A[i];
        parent[i] = -1;
    }

    int maxSum = A[0];
    int lastIndex = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i] && dp[j] + A[i] > dp[i]) {
                dp[i] = dp[j] + A[i];
                parent[i] = j;
            }
        }

        if (dp[i] > maxSum) {
            maxSum = dp[i];
            lastIndex = i;
        }
    }

    int length = 0;
    int current = lastIndex;

    while (current != -1) {
        length++;
        current = parent[current];
    }

    int *sequence = malloc(length * sizeof(int));

    if (sequence == NULL) {
        printf("Memory allocation failed.\n");
        free(dp);
        free(parent);
        return;
    }

    int index = length - 1;
    current = lastIndex;

    while (current != -1) {
        sequence[index] = A[current];
        index--;
        current = parent[current];
    }

    printf("Maximum Sum: %d\n", maxSum);

    printf("Maximum Sum Increasing Subsequence: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    free(sequence);
    free(dp);
    free(parent);
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid array size.\n");
        return 0;
    }

    int *A = malloc(n * sizeof(int));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    findMaximumSumIS(A, n);

    free(A);

    return 0;
}