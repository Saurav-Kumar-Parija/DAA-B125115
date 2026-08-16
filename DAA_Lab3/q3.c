#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int min;
    int max;
} Pair;

Pair getMinMax(int arr[], int low, int high, int *comps) {
    Pair result, left, right;
    int mid;

    // Base Case 1: If the array has only one element
    if (low == high) {
        result.max = arr[low];
        result.min = arr[low];
        return result;
    }

    // Base Case 2: If the array has exactly two elements
    if (high == low + 1) {
        (*comps)++; 
        if (arr[low] > arr[high]) {
            result.max = arr[low];
            result.min = arr[high];
        } else {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }

    mid = (low + high) / 2;
    left = getMinMax(arr, low, mid, comps);
    right = getMinMax(arr, mid + 1, high, comps);

    // Combine the results by comparing the max and min of both halves
    (*comps) += 2; 
    
    if (left.max > right.max) {
        result.max = left.max;
    } else {
        result.max = right.max;
    }

    if (left.min < right.min) {
        result.min = left.min;
    } else {
        result.min = right.min;
    }

    return result;
}

int main() {
    int n;
    int comparisons = 0;

    srand(time(NULL));

    printf("Enter the number of elements for the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Generated Array: ");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Generates a random number between 0 and 9999
        
        if (n <= 50) {
            printf("%d ", arr[i]);
        }
    }
    if (n > 50) {
        printf("[Array is too large to print entirely]");
    }
    printf("\n\n");
    Pair minmax = getMinMax(arr, 0, n - 1, &comparisons);

    printf("Minimum element is %d\n", minmax.min);
    printf("Maximum element is %d\n", minmax.max);
    printf("\n");
    printf("Elements in Array (n): %d\n", n);

    printf("Theoretical formula (3n/2 - 2): %d\n", (3 * n / 2) - 2);
    printf("Actual comparisons made: %d\n", comparisons);

    free(arr);

    return 0;
}