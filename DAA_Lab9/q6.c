#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII 256

typedef struct {
    char ch;
    int freq;
} Entry;

typedef struct {
    Entry data[ASCII];
    int size;
} MaxHeap;

typedef struct {
    char ch;
    int freq;
    int release;
} Waiting;

void swap(Entry *a, Entry *b) {
    Entry temp = *a;
    *a = *b;
    *b = temp;
}

void insert(MaxHeap *heap, char ch, int freq) {
    int i = heap->size++;
    heap->data[i].ch = ch;
    heap->data[i].freq = freq;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap->data[parent].freq >= heap->data[i].freq)
            break;

        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

Entry extractMax(MaxHeap *heap) {
    Entry result = heap->data[0];

    heap->size--;
    heap->data[0] = heap->data[heap->size];

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < heap->size &&
            heap->data[left].freq > heap->data[largest].freq)
            largest = left;

        if (right < heap->size &&
            heap->data[right].freq > heap->data[largest].freq)
            largest = right;

        if (largest == i)
            break;

        swap(&heap->data[i], &heap->data[largest]);
        i = largest;
    }

    return result;
}

int reorganize(const char *s, int k, char *result) {
    int count[ASCII] = {0};
    int n = strlen(s);

    if (k <= 1) {
        strcpy(result, s);
        return 1;
    }

    for (int i = 0; i < n; i++)
        count[(unsigned char)s[i]]++;

    MaxHeap heap = { .size = 0 };

    for (int i = 0; i < ASCII; i++) {
        if (count[i] > 0)
            insert(&heap, (char)i, count[i]);
    }

    Waiting waiting[ASCII];
    int front = 0, rear = 0;

    for (int pos = 0; pos < n; pos++) {
        while (front < rear && waiting[front].release <= pos) {
            insert(&heap, waiting[front].ch, waiting[front].freq);
            front++;
        }

        if (heap.size == 0) {
            result[0] = '\0';
            return 0;
        }

        Entry current = extractMax(&heap);
        result[pos] = current.ch;
        current.freq--;

        if (current.freq > 0) {
            waiting[rear].ch = current.ch;
            waiting[rear].freq = current.freq;
            waiting[rear].release = pos + k;
            rear++;
        }
    }

    result[n] = '\0';
    return 1;
}

int main() {
    char s[10001];
    char result[10001];
    int k;

    printf("Enter string: ");
    if (scanf("%10000s", s) != 1)
        return 1;

    printf("Enter K: ");
    if (scanf("%d", &k) != 1 || k < 0) {
        printf("Invalid K.\n");
        return 1;
    }

    if (reorganize(s, k, result))
        printf("Reorganised string: %s\n", result);
    else
        printf("Reorganised string: \"\" (impossible)\n");

    return 0;
}
