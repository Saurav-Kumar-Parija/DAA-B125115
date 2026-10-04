#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minCoinChange(int coins[], int n, int V)
{
    int *dp = (int *)malloc((V + 1) * sizeof(int));
    int *choice = (int *)malloc((V + 1) * sizeof(int));

    if (dp == NULL || choice == NULL)
    {
        free(dp);
        free(choice);
        return -1;
    }

    dp[0] = 0;
    choice[0] = -1;

    for (int i = 1; i <= V; i++)
    {
        dp[i] = INT_MAX;
        choice[i] = -1;
    }

    for (int amount = 1; amount <= V; amount++)
    {
        for (int i = 0; i < n; i++)
        {
            int coin = coins[i];

            if (coin <= amount && dp[amount - coin] != INT_MAX)
            {
                int current = dp[amount - coin] + 1;

                if (current < dp[amount])
                {
                    dp[amount] = current;
                    choice[amount] = coin;
                }
            }
        }
    }

    if (dp[V] == INT_MAX)
    {
        free(dp);
        free(choice);
        return -1;
    }

    printf("Minimum number of coins: %d\n", dp[V]);

    printf("Selected coins: ");

    int amount = V;

    while (amount > 0)
    {
        printf("%d ", choice[amount]);
        amount -= choice[amount];
    }

    printf("\n");
    int temp= dp[V];
    free(dp);
    free(choice);

    return temp;
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

    int result = minCoinChange(coins, n, V);
    printf("result: %d ", result);
    if (result == -1)
        printf("The target amount cannot be formed.\n");

    free(coins);

    return 0;
}