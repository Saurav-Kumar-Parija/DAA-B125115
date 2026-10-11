#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Meeting;

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int compareMeetings(const void *a, const void *b) {
    Meeting *m1 = (Meeting *)a;
    Meeting *m2 = (Meeting *)b;

    if (m1->start < m2->start)
        return -1;
    if (m1->start > m2->start)
        return 1;
    return 0;
}

void insert(MinHeap *heap, int value) {
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

int extractMin(MinHeap *heap) {
    int result = heap->data[0];

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

int minimumRooms(Meeting meetings[], int n) {
    if (n == 0)
        return 0;

    qsort(meetings, n, sizeof(Meeting), compareMeetings);

    MinHeap heap;
    heap.data = malloc(n * sizeof(int));
    heap.size = 0;
    heap.capacity = n;

    if (heap.data == NULL)
        return -1;

    int maximumRooms = 0;

    for (int i = 0; i < n; i++) {
        while (heap.size > 0 &&
               heap.data[0] <= meetings[i].start) {
            extractMin(&heap);
        }

        insert(&heap, meetings[i].end);

        if (heap.size > maximumRooms)
            maximumRooms = heap.size;
    }

    free(heap.data);
    return maximumRooms;
}

int main() {
    int n;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Invalid number of meetings.\n");
        return 1;
    }

    Meeting *meetings = malloc((n > 0 ? n : 1) * sizeof(Meeting));

    if (meetings == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter start and end times:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &meetings[i].start, &meetings[i].end);

        if (meetings[i].start >= meetings[i].end) {
            printf("Invalid meeting interval.\n");
            free(meetings);
            return 1;
        }
    }

    int result = minimumRooms(meetings, n);

    if (result == -1)
        printf("Memory allocation failed.\n");
    else
        printf("Minimum rooms required = %d\n", result);

    free(meetings);
    return 0;
}
