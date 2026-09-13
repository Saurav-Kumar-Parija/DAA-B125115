#include <stdio.h>

long long minimumMoves(int n)
{
    return (long long)n * (n + 1) / 6;
}

int main()
{
    int n;
    long long totalCoins, moves;

    printf("Enter the number of rows in the coin triangle: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of rows.\n");
        return 1;
    }

    totalCoins = (long long)n * (n + 1) / 2;
    moves = minimumMoves(n);

    printf("\nNumber of rows          : %d\n", n);
    printf("Total number of coins   : %lld\n", totalCoins);
    printf("Minimum number of moves : %lld\n", moves);

    return 0;
}