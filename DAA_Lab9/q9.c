#include <stdio.h>
#include <limits.h>

#define MAX 100

long long dp[MAX][MAX];
long long prefix[MAX + 1];
int split[MAX][MAX];

long long rangeSum(int i, int j) {
    return prefix[j + 1] - prefix[i];
}

void buildTree(int i, int j) {
    if (i == j) {
        printf("%d", i + 1);
        return;
    }

    int k = split[i][j];

    printf("(");
    buildTree(i, k);
    printf(",");
    buildTree(k + 1, j);
    printf(")");
}

long long optimalAlphabeticTree(int n) {
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
        split[i][i] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long cost =
                    dp[i][k] + dp[k + 1][j]
                    + rangeSum(i, j);

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    return dp[0][n - 1];
}

int main(void) {
    int n;
    long long weight[MAX];

    printf("Enter number of leaves: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of leaves.\n");
        return 1;
    }

    printf("Enter weights in their required order:\n");
    prefix[0] = 0;

    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &weight[i]) != 1 ||
            weight[i] < 0 ||
            prefix[i] > LLONG_MAX - weight[i]) {
            printf("Invalid weight or weight sum overflow.\n");
            return 1;
        }

        prefix[i + 1] = prefix[i] + weight[i];
    }

    long long cost = optimalAlphabeticTree(n);

    printf("Optimal weighted path length = %lld\n", cost);
    printf("Alphabetic tree: ");
    buildTree(0, n - 1);
    printf("\n");

    return 0;
}
