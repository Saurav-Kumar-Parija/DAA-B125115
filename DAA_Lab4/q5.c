#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int start;
    int end;
} Interval;

/* Compare intervals by starting time */
int compare(const void *a, const void *b)
{
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;

    return i1->start - i2->start;
}

/* Merge overlapping intervals */
int mergeIntervals(Interval arr[], int n, Interval result[])
{
    if (n == 0)
        return 0;

    /* Sort intervals by starting point */
    qsort(arr, n, sizeof(Interval), compare);

    int count = 0;

    result[count] = arr[0];
    count++;

    for (int i = 1; i < n; i++)
    {
        /*
           If current interval overlaps the last
           merged interval.
        */
        if (arr[i].start <= result[count - 1].end)
        {
            if (arr[i].end > result[count - 1].end)
                result[count - 1].end = arr[i].end;
        }
        else
        {
            /* No overlap */
            result[count] = arr[i];
            count++;
        }
    }

    return count;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Interval *intervals =
        malloc(n * sizeof(Interval));

    Interval *result =
        malloc(n * sizeof(Interval));

    if (intervals == NULL || result == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter intervals (start end):\n");

    for (int i = 0; i < n; i++)
    {
        printf("Interval %d: ", i + 1);
        scanf("%d %d",
              &intervals[i].start,
              &intervals[i].end);
    }

    int count =
        mergeIntervals(intervals, n, result);

    printf("\nMerged intervals:\n");

    for (int i = 0; i < count; i++)
    {
        printf("(%d, %d)",
               result[i].start,
               result[i].end);

        if (i != count - 1)
            printf(", ");
    }

    printf("\n");

    free(intervals);
    free(result);

    return 0;
}