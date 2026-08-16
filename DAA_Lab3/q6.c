#include <stdio.h>

void selectionSort(int A[], int n) {
    int i, j, min_index, temp;
    
    for (i = 0; i < n - 1; i++) {
        min_index = i;
        
        for (j = i + 1; j < n; j++) {
            if (A[j] < A[min_index]) {
                min_index = j;
            }
        }
        
        if (min_index != i) {
            temp = A[i];
            A[i] = A[min_index];
            A[min_index] = temp;
        }
    }
}

void printArray(int A[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {76, 26, 13, 22, 11};
    int n = sizeof(A) / sizeof(A[0]);
    
    printf("Original array: \n");
    printArray(A, n);
    
    selectionSort(A, n);
    
    printf("Sorted array: \n");
    printArray(A, n);
    
    return 0;
}