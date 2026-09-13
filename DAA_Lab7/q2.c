#include <stdio.h>

#define MAX_EGGS 100
#define MAX_FLOORS 100

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int eggDrop(int eggs, int floors)
{
    int dp[MAX_EGGS + 1][MAX_FLOORS + 1];
    int e, f, x;
    int worst;
    int best;

    // Base case: 0 floors require 0 drops //
    for (e = 1; e <= eggs; e++)
        dp[e][0] = 0;

    // Base case: 1 floor requires 1 drop //
    for (e = 1; e <= eggs; e++)
        dp[e][1] = 1;

    // Base case: 1 egg requires f drops //
    for (f = 1; f <= floors; f++)
        dp[1][f] = f;

    // Fill the DP table //
    for (e = 2; e <= eggs; e++){
        for (f = 2; f <= floors; f++){
            best = floors;
            // Try dropping the egg from every floor x //
            for (x = 1; x <= f; x++){
                /*
                   If egg breaks:
                   e-1 eggs and x-1 floors remain.

                   If egg survives:
                   e eggs and f-x floors remain.
                */
                worst = 1 + max(dp[e - 1][x - 1],
                                dp[e][f - x]);

                best = min(best, worst);
            }
            dp[e][f] = best;
        }
    }
    return dp[eggs][floors];
}

int main()
{
    int eggs, floors;
    int result;
    printf("Enter number of eggs: ");
    scanf("%d", &eggs);
    printf("Enter number of floors: ");
    scanf("%d", &floors);
    if (eggs <= 0 || floors < 0 ||
        eggs > MAX_EGGS || floors > MAX_FLOORS)
    {
        printf("Invalid input.\n");
        return 1;
    }

    result = eggDrop(eggs, floors);
    printf("\nNumber of eggs   : %d\n", eggs);
    printf("Number of floors : %d\n", floors);
    printf("Minimum drops    : %d\n", result);

    return 0;
}