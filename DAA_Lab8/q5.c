#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int **createDP(int m, int n)
{
    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    if (dp == NULL)
        return NULL;

    for (int i = 0; i <= m; i++)
    {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));

        if (dp[i] == NULL)
        {
            for (int k = 0; k < i; k++)
                free(dp[k]);

            free(dp);
            return NULL;
        }
    }

    return dp;
}

void freeDP(int **dp, int m)
{
    for (int i = 0; i <= m; i++)
        free(dp[i]);

    free(dp);
}

int lcsLength(char X[], char Y[], int m, int n, int **dp)
{
    for (int i = 0; i <= m; i++)
        dp[i][0] = 0;

    for (int j = 0; j <= n; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[m][n];
}

void reconstructLCS(char X[], char Y[], int m, int n,
                    int **dp, char lcs[])
{
    int length = dp[m][n];
    int index = length;

    lcs[index] = '\0';

    int i = m;
    int j = n;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index - 1] = X[i - 1];

            index--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
}

void printDPTable(char X[], char Y[], int m, int n, int **dp)
{
    printf("\nDP Table:\n\n");

    printf("    ");

    for (int j = 0; j < n; j++)
        printf("%3c", Y[j]);

    printf("\n");

    for (int i = 0; i <= m; i++)
    {
        if (i == 0)
            printf("  ");
        else
            printf("%c ", X[i - 1]);

        for (int j = 0; j <= n; j++)
            printf("%3d", dp[i][j]);

        printf("\n");
    }
}

int main()
{
    char X[100], Y[100];

    printf("Enter first sequence: ");
    scanf("%99s", X);

    printf("Enter second sequence: ");
    scanf("%99s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    int **dp = createDP(m, n);

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int length = lcsLength(X, Y, m, n, dp);

    char *lcs = (char *)malloc((length + 1) * sizeof(char));

    if (lcs == NULL)
    {
        freeDP(dp, m);
        printf("Memory allocation failed.\n");
        return 1;
    }

    reconstructLCS(X, Y, m, n, dp, lcs);

    printf("\nLength of LCS: %d\n", length);
    printf("LCS: %s\n", lcs);

    printDPTable(X, Y, m, n, dp);

    free(lcs);
    freeDP(dp, m);

    return 0;
}