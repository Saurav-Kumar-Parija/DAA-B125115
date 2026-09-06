#include <stdio.h>
#include <limits.h>

int min(int a, int b){
    return (a < b) ? a : b;
}

int main(){
    int N, i, j, k, chainLength;

    printf("Enter number of dimensions: ");
    scanf("%d", &N);

    int arr[N];
    printf("Enter the dimensions:\n");
    for (i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    for (i = 1; i < N; i++){
        printf("A%d: %d x %d\n", i, arr[i-1], arr[i]);
    }
    int dp[N][N];

    /* Cost of multiplying one matrix is 0 */
    for (i = 1; i < N; i++){
        dp[i][i] = 0;
    }

    /* chainLength is the number of matrices in the chain */
    for (chainLength = 2; chainLength < N; chainLength++){
        for (i = 1; i < N - chainLength + 1; i++){
            j = i + chainLength - 1;

            dp[i][j] = INT_MAX;
            for (k = i; k < j; k++){
                int cost = dp[i][k]
                         + dp[k + 1][j]
                         + arr[i - 1] * arr[k] * arr[j];

                if (cost < dp[i][j]){
                    dp[i][j] = cost;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %d\n\n",
           dp[1][N - 1]);

    return 0;
}