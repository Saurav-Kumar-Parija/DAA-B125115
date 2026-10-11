#include <stdio.h>
#include <stdlib.h>

void leftToRight(int rating[], int candies[], int n) {
    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1])
            candies[i] = candies[i - 1] + 1;
    }
}

void rightToLeft(int rating[], int candies[], int n) {
    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1] &&
            candies[i] <= candies[i + 1]) {
            candies[i] = candies[i + 1] + 1;
        }
    }
}

long long calculateTotal(int candies[], int n) {
    long long total = 0;

    for (int i = 0; i < n; i++)
        total += candies[i];

    return total;
}

int main() {
    int n;

    printf("Enter number of children: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Invalid number of children.\n");
        return 1;
    }

    if (n == 0) {
        printf("Minimum total candies = 0\n");
        return 0;
    }

    int *rating = malloc(n * sizeof(int));
    int *candies = malloc(n * sizeof(int));

    if (rating == NULL || candies == NULL) {
        printf("Memory allocation failed.\n");
        free(rating);
        free(candies);
        return 1;
    }

    printf("Enter ratings:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &rating[i]) != 1) {
            printf("Invalid input.\n");
            free(rating);
            free(candies);
            return 1;
        }

        candies[i] = 1;
    }

    leftToRight(rating, candies, n);
    rightToLeft(rating, candies, n);

    printf("\nRating\tCandies\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%d\n", rating[i], candies[i]);

    printf("\nMinimum total candies = %lld\n",
           calculateTotal(candies, n));

    free(rating);
    free(candies);

    return 0;
}
