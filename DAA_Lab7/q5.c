#include <stdio.h>
#include <stdlib.h>

void generateShots(int n, int shots[], int *count)
{
    int i;

    *count = 0;

    if (n == 2)
    {
        shots[(*count)++] = 1;
        shots[(*count)++] = 1;
        return;
    }

    if (n % 2 == 1)
    {
        for (i = 2; i <= n - 1; i++)
            shots[(*count)++] = i;

        for (i = 2; i <= n - 1; i++)
            shots[(*count)++] = i;
    }
    else
    {
        for (i = 2; i <= n - 1; i++)
            shots[(*count)++] = i;

        for (i = n - 1; i >= 2; i--)
            shots[(*count)++] = i;
    }
}

void printPossible(int possible[], int n)
{
    int i;

    printf("{ ");

    for (i = 1; i <= n; i++)
    {
        if (possible[i])
            printf("%d ", i);
    }

    printf("}");
}

int main()
{
    int n, i, j;
    int count;
    int *shots;
    int *possible;
    int *next;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("Invalid number of hiding spots.\n");
        return 1;
    }

    shots = malloc(2 * n * sizeof(int));
    possible = calloc(n + 1, sizeof(int));
    next = calloc(n + 1, sizeof(int));

    generateShots(n, shots, &count);

    for (i = 1; i <= n; i++)
        possible[i] = 1;

    printf("\nHitting a Moving Target\n");
    printf("-----------------------\n");

    printf("Number of spots: %d\n", n);

    printf("Shooting sequence: ");
    for (i = 0; i < count; i++)
        printf("%d ", shots[i]);

    printf("\n\n");

    printf("Step 0: Possible positions = ");
    printPossible(possible, n);
    printf("\n");

    for (i = 0; i < count; i++)
    {
        // Target is hit if it is at the shot position 
        possible[shots[i]] = 0;

        printf("Shot %d at spot %d: Possible positions = ",
               i + 1, shots[i]);

        printPossible(possible, n);
        printf("\n");

        // Move target to an adjacent spot 
        for (j = 1; j <= n; j++)
            next[j] = 0;

        for (j = 1; j <= n; j++)
        {
            if (possible[j])
            {
                if (j > 1)
                    next[j - 1] = 1;

                if (j < n)
                    next[j + 1] = 1;
            }
        }

        for (j = 1; j <= n; j++)
            possible[j] = next[j];

        if (i != count - 1)
        {
            printf("       After movement: Possible positions = ");
            printPossible(possible, n);
            printf("\n");
        }
    }

    printf("\nResult: ");

    for (i = 1; i <= n; i++)
    {
        if (possible[i])
        {
            printf("Strategy failed.\n");

            free(shots);
            free(possible);
            free(next);

            return 0;
        }
    }

    printf("Target is guaranteed to be hit.\n");

    free(shots);
    free(possible);
    free(next);

    return 0;
}