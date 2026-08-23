#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    char colour[10];
} Item;

void sortByColour(Item arr[], int n) {
    Item *red = malloc(n * sizeof(Item));
    Item *blue = malloc(n * sizeof(Item));
    Item *yellow = malloc(n * sizeof(Item));

    int r = 0, b = 0, y = 0;

    // Single pass through the already number-sorted input
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].colour, "Red") == 0)
            red[r++] = arr[i];

        else if (strcmp(arr[i].colour, "Blue") == 0)
            blue[b++] = arr[i];

        else if (strcmp(arr[i].colour, "Yellow") == 0)
            yellow[y++] = arr[i];
    }

    // Combine: Red -> Blue -> Yellow
    int k = 0;

    for (int i = 0; i < r; i++)
        arr[k++] = red[i];

    for (int i = 0; i < b; i++)
        arr[k++] = blue[i];

    for (int i = 0; i < y; i++)
        arr[k++] = yellow[i];

    free(red);
    free(blue);
    free(yellow);
}

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item *arr = malloc(n * sizeof(Item));

    printf("Enter items in increasing order of number:\n");

    for (int i = 0; i < n; i++) {
        printf("Item %d (number colour): ", i + 1);
        scanf("%d %s", &arr[i].number, arr[i].colour);
    }

    sortByColour(arr, n);

    printf("\nSorted by colour:\n");
    printf("Number\tColour\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%s\n", arr[i].number, arr[i].colour);

    free(arr);

    return 0;
}