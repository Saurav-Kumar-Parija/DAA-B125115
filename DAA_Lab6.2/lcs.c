#include <stdio.h>
#include <string.h>

int max(int a, int b){
    return (a > b) ? a : b;
}

int main(){
    char X[100], Y[100];
    int m, n;
    int i, j;

    printf("Enter first string: ");
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);

    m = strlen(X);
    n = strlen(Y);
    int dp[m + 1][n + 1];

    /* Build the DP table */
    for (i = 0; i <= m; i++){
        for (j = 0; j <= n; j++){
            if (i == 0 || j == 0){
                dp[i][j] = 0;
            }
            else if (X[i - 1] == Y[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    printf("\nLength of LCS = %d\n", dp[m][n]);

    /* Construct the LCS */
    int length = dp[m][n];
    char lcs[length + 1];
    lcs[length] = '\0';
    i = m;
    j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]){
            lcs[length - 1] = X[i - 1];
            i--;
            j--;
            length--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]){
            i--;
        }
        else{
            j--;
        }
    }
    printf("Longest Common Subsequence = %s\n", lcs);
    return 0;
}