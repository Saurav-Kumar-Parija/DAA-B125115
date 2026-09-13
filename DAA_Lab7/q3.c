#include <stdio.h>
#include <limits.h>

#define MAX_DISKS 100

long long powerOfTwo(int n)
{
    long long result = 1;

    for (int i = 0; i < n; i++)
        result *= 2;

    return result;
}

void revePuzzle(int n)
{
    long long dp[MAX_DISKS + 1];
    int split[MAX_DISKS + 1];
    dp[0] = 0;
    split[0] = 0;
    if (n >= 1)
    {
        dp[1] = 1;
        split[1] = 0;
    }
    /*
       Calculate minimum moves for each number
       of disks.
    */
    for (int disks = 2; disks <= n; disks++)
    {
        dp[disks] = LLONG_MAX;
        /*
           Try every possible value of k.
           k disks are moved using 4 pegs.
           The remaining disks are moved using
           the ordinary 3-peg Tower of Hanoi.
        */
        for (int k = 1; k < disks; k++)
        {
            long long moves =
                2 * dp[k]
                + powerOfTwo(disks - k)
                - 1;
            if (moves < dp[disks])
            {
                dp[disks] = moves;
                split[disks] = k;
            }
        }
    }

    printf("\nMinimum number of moves = %lld\n", dp[n]);
    printf("Optimal split k = %d\n", split[n]);
    printf("\nDP Table:\n");
    printf("Disks\tMinimum Moves\tBest k\n");
    for (int i = 0; i <= n; i++)
    {
        printf("%d\t%lld\t\t%d\n",
               i, dp[i], split[i]);
    }
}

int main()
{
    int n;
    printf("Enter number of disks: ");
    scanf("%d", &n);
    if (n < 1 || n > MAX_DISKS)
    {
        printf("Invalid number of disks.\n");
        return 1;
    }
    revePuzzle(n);

    return 0;
}