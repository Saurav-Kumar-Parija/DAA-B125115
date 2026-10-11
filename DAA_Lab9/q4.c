#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long *data;
    int size;
    int capacity;
} MinHeap;

void swap(long long *a, long long *b) {
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void insert(MinHeap *heap, long long value) {
    int i = heap->size++;
    heap->data[i] = value;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap->data[parent] <= heap->data[i])
            break;

        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

long long extractMin(MinHeap *heap) {
    long long result = heap->data[0];

    heap->size--;
    heap->data[0] = heap->data[heap->size];

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size &&
            heap->data[left] < heap->data[smallest])
            smallest = left;

        if (right < heap->size &&
            heap->data[right] < heap->data[smallest])
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap->data[i], &heap->data[smallest]);
        i = smallest;
    }

    return result;
}

long long minimumCost(long long sticks[], int n) {
    if (n <= 1)
        return 0;

    MinHeap heap;
    heap.data = malloc(n * sizeof(long long));
    heap.size = 0;
    heap.capacity = n;

    if (heap.data == NULL)
        return -1;

    for (int i = 0; i < n; i++)
        insert(&heap, sticks[i]);

    long long totalCost = 0;

    while (heap.size > 1) {
        long long x = extractMin(&heap);
        long long y = extractMin(&heap);
        long long combined = x + y;

        printf("Connect %lld and %lld: cost = %lld\n",
               x, y, combined);

        totalCost += combined;
        insert(&heap, combined);
    }

    free(heap.data);
    return totalCost;
}

int main() {
    int n;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Invalid number of sticks.\n");
        return 1;
    }

    long long *sticks = malloc((n > 0 ? n : 1) * sizeof(long long));

    if (sticks == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter stick lengths:\n");

    for (int i = 0; i < n; i++) {
        scanf("%lld", &sticks[i]);

        if (sticks[i] < 0) {
            printf("Stick lengths cannot be negative.\n");
            free(sticks);
            return 1;
        }
    }

    long long result = minimumCost(sticks, n);

    if (result == -1) {
        printf("Memory allocation failed.\n");
    } else {
        printf("Minimum total cost = %lld\n", result);
    }

    free(sticks);
    return 0;
}
