#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int point;
    int type;       // +1 = start, -1 = end
} Event;

int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    return e2->type - e1->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event *events = malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter intervals (left right):\n");

    for (int i = 0; i < n; i++)
    {
        int left, right;

        printf("Interval %d: ", i + 1);
        scanf("%d %d", &left, &right);

        events[2 * i].point = left;
        events[2 * i].type = 1;

        events[2 * i + 1].point = right;
        events[2 * i + 1].type = -1;
    }

    // Sort events 
    qsort(events, 2 * n, sizeof(Event), compare);

    // Find maximum overlap 
    int current = 0;
    int maximum = 0;

    for (int i = 0; i < 2 * n; i++)
    {
        current += events[i].type;

        if (current > maximum)
            maximum = current;
    }

    printf("\nMaximum number of overlapping intervals: %d\n",
           maximum);

    
    // Find all points at which the maximum is reached.
    
    current = 0;

    printf("Points where maximum overlap begins:\n");

    for (int i = 0; i < 2 * n; i++)
    {
        current += events[i].type;

        if (current == maximum &&
            (i == 0 || events[i - 1].point != events[i].point))
        {
            printf("%d ", events[i].point);
        }
    }

    printf("\n");

    free(events);

    return 0;
}