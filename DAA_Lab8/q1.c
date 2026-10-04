#include <stdio.h>
#include <stdlib.h>

long long countWays(int coins[], int n, int V)
{
    long long *dp = (long long *)malloc((V + 1) * sizeof(long long));

    if (dp == NULL)
        return -1;

    dp[0] = 1;

    for (int i = 1; i <= V; i++)
        dp[i] = 0;

    for (int i = 0; i < n; i++)
    {
        for (int amount = coins[i]; amount <= V; amount++)
        {
            dp[amount] += dp[amount - coins[i]];
        }
    }

    long long result = dp[V];

    free(dp);

    return result;
}

void printCombinations(int coins[], int n, int remaining,
                       int start, int combination[], int length)
{
    if (remaining == 0)
    {
        printf("[ ");

        for (int i = 0; i < length; i++)
            printf("%d ", combination[i]);

        printf("]\n");

        return;
    }

    for (int i = start; i < n; i++)
    {
        if (coins[i] <= remaining)
        {
            combination[length] = coins[i];

            printCombinations(
                coins,
                n,
                remaining - coins[i],
                i,
                combination,
                length + 1
            );
        }
    }
}

int main()
{
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int *coins = (int *)malloc(n * sizeof(int));

    if (coins == NULL)
        return 1;

    printf("Enter coin denominations: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    long long ways = countWays(coins, n, V);

    if (ways == -1)
    {
        printf("Memory allocation failed.\n");
        free(coins);
        return 1;
    }

    printf("\nTotal number of ways: %lld\n", ways);

    if (ways > 0)
    {
        int *combination = (int *)malloc((V + 1) * sizeof(int));

        if (combination == NULL)
        {
            free(coins);
            return 1;
        }

        printf("\nAll combinations:\n");

        printCombinations(
            coins,
            n,
            V,
            0,
            combination,
            0
        );

        free(combination);
    }
    else
    {
        printf("No combination can form the target amount.\n");
    }

    free(coins);

    return 0;
}