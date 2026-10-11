#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 2000

int overlapLength(const char *a, const char *b) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int limit = lenA < lenB ? lenA : lenB;

    for (int len = limit; len > 0; len--) {
        if (strncmp(a + lenA - len, b, len) == 0)
            return len;
    }

    return 0;
}

void removeString(char strings[][MAX_LENGTH], int *n, int index) {
    for (int i = index; i < *n - 1; i++)
        strcpy(strings[i], strings[i + 1]);

    (*n)--;
}

void removeContained(char strings[][MAX_LENGTH], int *n) {
    int i = 0;

    while (i < *n) {
        int contained = 0;

        for (int j = 0; j < *n; j++) {
            if (i == j)
                continue;

            if (strcmp(strings[i], strings[j]) == 0 && j > i)
                continue;

            if (strstr(strings[j], strings[i]) != NULL) {
                contained = 1;
                break;
            }
        }

        if (contained)
            removeString(strings, n, i);
        else
            i++;
    }
}

int greedySuperstring(char strings[][MAX_LENGTH], int n,
                      char result[MAX_LENGTH]) {
    removeContained(strings, &n);

    while (n > 1) {
        int bestI = -1;
        int bestJ = -1;
        int bestOverlap = -1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j)
                    continue;

                int overlap = overlapLength(strings[i], strings[j]);

                if (overlap > bestOverlap) {
                    bestOverlap = overlap;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        if (bestI == -1 || bestJ == -1)
            return 0;

        int lenA = strlen(strings[bestI]);
        int lenB = strlen(strings[bestJ]);
        int newLength = lenA + lenB - bestOverlap;

        if (newLength >= MAX_LENGTH)
            return 0;

        strcat(strings[bestI], strings[bestJ] + bestOverlap);
        removeString(strings, &n, bestJ);
    }

    strcpy(result, strings[0]);
    return 1;
}

int main(void) {
    int n;
    char strings[MAX_STRINGS][MAX_LENGTH];
    char result[MAX_LENGTH];

    printf("Enter number of strings: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_STRINGS) {
        printf("Invalid number of strings.\n");
        return 1;
    }

    printf("Enter the strings:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%1999s", strings[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    if (!greedySuperstring(strings, n, result)) {
        printf("Superstring exceeds the supported limit.\n");
        return 1;
    }

    printf("Greedy superstring: %s\n", result);
    printf("Length: %zu\n", strlen(result));

    return 0;
}
