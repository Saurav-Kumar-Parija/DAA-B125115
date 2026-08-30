#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "heap_sort_input.txt"

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i)
    {
        swap(&a[i], &a[largest]);

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);

        heapify(a, i, 0);
    }
}

void generateFile(int n)
{
    FILE *fp = fopen(FILENAME, "w");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        int value = rand() % 1000;
        fprintf(fp, "%d ", value);
    }

    fclose(fp);
}

void readFromFile(int a[], int n)
{
    FILE *fp = fopen(FILENAME, "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &a[i]);
    }

    fclose(fp);
}

void display(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of elements.\n");
        return 0;
    }

    int *a = (int *)malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    srand(time(NULL));

    generateFile(n);

    readFromFile(a, n);

    printf("\nElements read from file:\n");
    display(a, n);

    heapSort(a, n);

    printf("\nSorted elements using Heap Sort:\n");
    display(a, n);

    free(a);

    return 0;
}