#include <stdio.h>
#include <stdlib.h>

int isValidMove(int state, int pos, int n)
{
    int i;

    //Rightmost switch can always be toggled 
    if (pos == n - 1)
        return 1;

    //Immediate right switch must be ON 
    if (((state >> (n - pos - 2)) & 1) == 0)
        return 0;

    //All switches further right must be OFF 
    for (i = pos + 2; i < n; i++)
    {
        if (((state >> (n - i - 1)) & 1) == 1)
            return 0;
    }

    return 1;
}

void printState(int state, int n)
{
    int i;

    for (i = n - 1; i >= 0; i--)
        printf("%d", (state >> i) & 1);
}

void solve(int n)
{
    int totalStates = 1 << n;
    int start = totalStates - 1;
    int goal = 0;

    int *queue = malloc(totalStates * sizeof(int));
    int *parent = malloc(totalStates * sizeof(int));
    int *visited = calloc(totalStates, sizeof(int));
    int *path = malloc(totalStates * sizeof(int));

    int front = 0, rear = 0;
    int current, next;
    int i, j;
    int pathLength = 0;

    queue[rear++] = start;
    visited[start] = 1;
    parent[start] = -1;

    while (front < rear)
    {
        current = queue[front++];

        if (current == goal)
            break;

        for (i = 0; i < n; i++)
        {
            if (isValidMove(current, i, n))
            {
                next = current ^ (1 << (n - i - 1));

                if (!visited[next])
                {
                    visited[next] = 1;
                    parent[next] = current;
                    queue[rear++] = next;
                }
            }
        }
    }

    current = goal;

    while (current != -1)
    {
        path[pathLength++] = current;
        current = parent[current];
    }

    printf("\nSecurity Switches\n");
    printf("-----------------\n");
    printf("Number of switches: %d\n", n);
    printf("Minimum moves: %d\n\n", pathLength - 1);

    printf("Step\tSwitch State\n");
    printf("----\t------------\n");

    for (i = pathLength - 1, j = 0; i >= 0; i--, j++)
    {
        printf("%d\t", j);
        printState(path[i], n);
        printf("\n");
    }

    free(queue);
    free(parent);
    free(visited);
    free(path);
}

int main()
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0 || n >= 31)
    {
        printf("Invalid number of switches.\n");
        return 1;
    }

    solve(n);

    return 0;
}