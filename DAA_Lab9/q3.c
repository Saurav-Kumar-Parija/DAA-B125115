#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int distance;
    int fuel;
} Station;

typedef struct {
    int *data;
    int size;
    int capacity;
} MaxHeap;

int compareStations(const void *a, const void *b) {
    const Station *x = a;
    const Station *y = b;

    return (x->distance > y->distance) -
           (x->distance < y->distance);
}

void insert(MaxHeap *heap, int fuel) {
    int i = heap->size++;

    heap->data[i] = fuel;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap->data[parent] >= heap->data[i])
            break;

        int temp = heap->data[parent];
        heap->data[parent] = heap->data[i];
        heap->data[i] = temp;

        i = parent;
    }
}

int extractMax(MaxHeap *heap) {
    int result = heap->data[0];

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

        int temp = heap->data[i];
        heap->data[i] = heap->data[largest];
        heap->data[largest] = temp;

        i = largest;
    }

    return result;
}

int minimumStops(int D, int F, Station stations[], int n) {
    qsort(stations, n, sizeof(Station), compareStations);

    MaxHeap heap;
    heap.data = malloc((n > 0 ? n : 1) * sizeof(int));
    heap.size = 0;
    heap.capacity = n;

    int reach = F;
    int stops = 0;

    for (int i = 0; i <= n; i++) {
        int destination = (i == n) ? D : stations[i].distance;

        while (reach < destination) {
            if (heap.size == 0) {
                free(heap.data);
                return -1;
            }

            reach += extractMax(&heap);
            stops++;
        }

        if (i < n)
            insert(&heap, stations[i].fuel);
    }

    free(heap.data);
    return stops;
}

int main() {
    int n, D, F;

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter initial fuel: ");
    scanf("%d", &F);

    printf("Enter number of fuel stations: ");
    scanf("%d", &n);

    if (n < 0 || D < 0 || F < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    Station *stations = malloc((n > 0 ? n : 1) * sizeof(Station));

    if (stations == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter station distance and fuel amount:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &stations[i].distance,
              &stations[i].fuel);

        if (stations[i].distance < 0 ||
            stations[i].distance > D ||
            stations[i].fuel < 0) {
            printf("Invalid station data.\n");
            free(stations);
            return 1;
        }
    }

    int result = minimumStops(D, F, stations, n);

    if (result == -1)
        printf("Target cannot be reached.\n");
    else
        printf("Minimum refuelling stops = %d\n", result);

    free(stations);
    return 0;
}
