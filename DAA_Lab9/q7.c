#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long *data;
    int size;
    int capacity;
} MaxHeap;

void swap(long long *a, long long *b) {
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void insert(MaxHeap *heap, long long value) {
    int i = heap->size++;
    heap->data[i] = value;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap->data[parent] >= heap->data[i])
            break;

        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

long long extractMax(MaxHeap *heap) {
    long long result = heap->data[0];

    heap->size--;
    heap->data[0] = heap->data[heap->size];

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < heap->size &&
            heap->data[left] > heap->data[largest])
            largest = left;

        if (right < heap->size &&
            heap->data[right] > heap->data[largest])
            largest = right;

        if (largest == i)
            break;

        swap(&heap->data[i], &heap->data[largest]);
        i = largest;
    }

    return result;
}

long long minimizeDeviation(long long A[], int n) {
    MaxHeap heap;
    heap.data = malloc(n * sizeof(long long));
    heap.size = 0;
    heap.capacity = n;

    if (heap.data == NULL)
        return -1;

    long long minimum = LLONG_MAX;
    long long answer = LLONG_MAX;

    for (int i = 0; i < n; i++) {
        long long x = A[i];

        if (x % 2 != 0)
            x *= 2;

        insert(&heap, x);

        if (x < minimum)
            minimum = x;
    }

    while (1) {
        long long maximum = extractMax(&heap);
        long long deviation = maximum - minimum;

        if (deviation < answer)
            answer = deviation;

        if (maximum % 2 != 0)
            break;

        maximum /= 2;

        if (maximum < minimum)
            minimum = maximum;

        insert(&heap, maximum);
    }

    free(heap.data);
    return answer;
}

int main() {
    int n;

    printf("Enter array size: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 1;
    }

    long long *A = malloc(n * sizeof(long long));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter positive integers:\n");

    for (int i = 0; i < n; i++) {
        scanf("%lld", &A[i]);

        if (A[i] <= 0 || A[i] > LLONG_MAX / 2) {
            printf("Invalid element.\n");
            free(A);
            return 1;
        }
    }

    long long result = minimizeDeviation(A, n);

    if (result == -1)
        printf("Memory allocation failed.\n");
    else
        printf("Minimum deviation = %lld\n", result);

    free(A);
    return 0;
}
