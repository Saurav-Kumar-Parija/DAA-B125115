#include <stdio.h>
#include <stdlib.h>

int rodCutting(int price[], int n) {
    int *dp = malloc((n + 1) * sizeof(int));
    int *cut = malloc((n + 1) * sizeof(int));

    if (dp == NULL || cut == NULL) {
        printf("Memory allocation failed.\n");
        free(dp);
        free(cut);
        return -1;
    }

    dp[0] = 0;
    cut[0] = 0;

    for (int i = 1; i <= n; i++) {
        dp[i] = price[i];
        cut[i] = i;

        for (int j = 1; j <= i; j++) {
            if (price[j] + dp[i - j] > dp[i]) {
                dp[i] = price[j] + dp[i - j];
                cut[i] = j;
            }
        }
    }

    printf("Maximum Revenue: %d\n", dp[n]);

    printf("Cuts: ");

    int length = n;

    while (length > 0) {
        printf("%d ", cut[length]);
        length -= cut[length];
    }

    printf("\n");

    int result = dp[n];

    free(dp);
    free(cut);

    return result;
}

int main() {
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid rod length.\n");
        return 0;
    }

    int *price = malloc((n + 1) * sizeof(int));

    if (price == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    price[0] = 0;

    printf("Enter prices for lengths 1 to %d:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &price[i]);

    rodCutting(price, n);

    free(price);

    return 0;
}