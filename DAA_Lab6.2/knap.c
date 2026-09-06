#include <stdio.h>

int max(int a, int b){
    return (a > b) ? a : b;
}

int main(){
    int n, W;
    int i, w;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int weight[n], profit[n];

    printf("Enter weights of items:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &weight[i]);

    printf("Enter profits of items:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &profit[i]);

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    int dp[n + 1][W + 1];
    // Build DP table 
    for (i = 0; i <= n; i++){
        for (w = 0; w <= W; w++){
            if (i == 0 || w == 0){
                dp[i][w] = 0;
            }
            else if (weight[i - 1] <= w){
                dp[i][w] = max(
                    profit[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else{
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("\nMaximum Profit = %d\n", dp[n][W]);

    // Find selected items 
    i = n;
    w = W;
    printf("Selected Items: ");
    while (i > 0 && w > 0){
        if (dp[i][w] != dp[i - 1][w]){
            printf("%d ", i);
            w = w - weight[i - 1];
        }

        i--;
    }
    printf("\n");
    return 0;
}