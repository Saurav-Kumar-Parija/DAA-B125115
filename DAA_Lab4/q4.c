#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int time;
    int type;       // +1 = entry, -1 = exit
} Event;

// Compare two events by time 
int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    return e1->time - e2->time;
}

int main()
{
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    Event *events = malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter entry and exit time for each person:\n");

    for (int i = 0; i < n; i++)
    {
        int entry, exit;

        printf("Person %d: ", i + 1);
        scanf("%d %d", &entry, &exit);

        events[2 * i].time = entry;
        events[2 * i].type = 1;

        events[2 * i + 1].time = exit;
        events[2 * i + 1].type = -1;
    }

    // Sort all events by time 
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maximum = 0;
    int maxTime = 0;

    // Scan sorted events
    for (int i = 0; i < 2 * n; i++)
    {
        current += events[i].type;

        if (current > maximum)
        {
            maximum = current;
            maxTime = events[i].time;
        }
    }

    printf("\n----------------------------------\n");
    printf("Maximum people present: %d\n", maximum);
    printf("Time when maximum occurred: %d\n", maxTime);
    printf("----------------------------------\n");

    free(events);

    return 0;
}