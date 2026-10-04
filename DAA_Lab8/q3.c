#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long ull;

int isEven(ull n) {
    return n % 2 == 0;
}

int nextCollatz(ull n, ull *next) {
    if (isEven(n)) {
        *next = n / 2;
        return 1;
    }

    if (n > (ULLONG_MAX - 1) / 3)
        return 0;

    *next = 3 * n + 1;
    return 1;
}

ull *generateSequence(ull n, size_t *length, int *overflow) {
    size_t capacity = 16;
    size_t count = 0;

    ull *sequence = malloc(capacity * sizeof(ull));

    if (sequence == NULL)
        return NULL;

    *overflow = 0;

    while (1) {
        if (count == capacity) {
            capacity *= 2;

            ull *temp = realloc(sequence,
                                 capacity * sizeof(ull));

            if (temp == NULL) {
                free(sequence);
                return NULL;
            }

            sequence = temp;
        }

        sequence[count++] = n;

        if (n == 1)
            break;

        ull next;

        if (!nextCollatz(n, &next)) {
            *overflow = 1;
            break;
        }

        n = next;
    }

    *length = count;
    return sequence;
}

void printSequence(ull *sequence, size_t length) {
    printf("Sequence: ");

    for (size_t i = 0; i < length; i++) {
        printf("%llu", sequence[i]);

        if (i != length - 1)
            printf(" -> ");
    }

    printf("\n");
}

void analyzeNumber(ull n) {
    size_t length;
    int overflow;

    ull *sequence = generateSequence(n, &length, &overflow);

    if (sequence == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("\nStarting number: %llu\n", n);

    printSequence(sequence, length);

    if (overflow) {
        printf("Overflow detected. Sequence stopped safely.\n");
    } else {
        printf("Number of terms: %zu\n", length);
        printf("Steps to reach 1: %zu\n", length - 1);
    }

    free(sequence);
}

void analyzeRange(ull a, ull b) {
    if (a > b) {
        ull temp = a;
        a = b;
        b = temp;
    }

    printf("\nCollatz Analysis for [%llu, %llu]\n", a, b);

    for (ull n = a; n <= b; n++) {
        size_t length;
        int overflow;

        ull *sequence = generateSequence(n, &length, &overflow);

        if (sequence == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        printf("\n%llu: ", n);

        if (overflow) {
            printf("overflow detected");
        } else {
            printf("%zu steps", length - 1);
        }

        free(sequence);

        if (n == ULLONG_MAX)
            break;
    }
}

int main() {
    ull n, a, b;

    printf("Enter starting number n: ");
    scanf("%llu", &n);

    if (n == 0) {
        printf("Starting number must be positive.\n");
        return 0;
    }

    printf("Enter interval [a b]: ");
    scanf("%llu %llu", &a, &b);

    if (a == 0 || b == 0) {
        printf("Interval values must be positive.\n");
        return 0;
    }

    analyzeNumber(n);
    analyzeRange(a, b);

    return 0;
}