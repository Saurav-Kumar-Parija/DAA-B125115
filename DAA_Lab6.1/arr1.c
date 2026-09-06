#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

// Function Prototypes 
int findMaximum(int A[], int n);
void findLargestAndSecondLargest(int A[], int n);
double findMean(int A[], int n);
double findMedian(int A[], int n);
double findStandardDeviation(int A[], int n);
int findMode(int A[], int n);
int removeDuplicates(int A[], int n);
void reverseArray(int A[], int n);
void partitionArray(int A[], int n, int pivot);
void copyArray(int source[], int destination[], int n);
void displayArray(int A[], int n);

// (i) Find Maximum 
int findMaximum(int A[], int n){
    int i;
    int maximum = A[0];
    for (i = 1; i < n; i++){
        if (A[i] > maximum){
            maximum = A[i];
        }
    }
    return maximum;
}

// (ii) Find First and Second Largest 
void findLargestAndSecondLargest(int A[], int n){
    int i;
    int largest = INT_MIN;
    int secondLargest = INT_MIN;
    for (i = 0; i < n; i++){
        if (A[i] > largest){
            secondLargest = largest;
            largest = A[i];
        }
        else if (A[i] > secondLargest){
            secondLargest = A[i];
        }
    }
    printf("Largest element = %d\n", largest);
    printf("Second largest element = %d\n", secondLargest);
}

// (iii) Find Mean 
double findMean(int A[], int n){
    int i;
    double sum = 0;
    for (i = 0; i < n; i++){
        sum = sum + A[i];
    }
    return sum / n;
}

// (iv) Find Median 
double findMedian(int A[], int n){
    int i, j, temp;
    double median;
    /*Bubble Sort
     We use a copy of the array before calling
    this function, so the original array is preserved.*/

    
    for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - i - 1; j++){
            if (A[j] > A[j + 1]){
                temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }

    if (n % 2 == 1){
        median = A[n / 2];
    }
    else{
        median = (A[n / 2 - 1] + A[n / 2]) / 2.0;
    }
    return median;
}

// (v) Find Standard Deviation 
double findStandardDeviation(int A[], int n){
    int i;
    double sum = 0;
    double mean;
    double squaredSum = 0;
    double variance;
    // Calculate mean 
    for (i = 0; i < n; i++){
        sum = sum + A[i];
    }
    mean = sum / n;

    // Calculate squared differences 
    for (i = 0; i < n; i++){
        squaredSum = squaredSum +
                     (A[i] - mean) * (A[i] - mean);
    }
    variance = squaredSum / n;
    return sqrt(variance);
}

// (vi) Find Mode 
int findMode(int A[], int n){
    int i, j;
    int mode = A[0];
    int maxCount = 0;
    for (i = 0; i < n; i++){
        int count = 0;
        for (j = 0; j < n; j++){
            if (A[j] == A[i]){
                count++;
            }
        }
        if (count > maxCount){
            maxCount = count;
            mode = A[i];
        }
    }
    return mode;
}

// (vii) Remove All Duplicates 
int removeDuplicates(int A[], int n){
    int i, j;
    int newSize = 0;
    int duplicate;
    for (i = 0; i < n; i++){
        duplicate = 0;
        for (j = 0; j < newSize; j++) {
            if (A[j] == A[i]){
                duplicate = 1;
                break;
            }
        }
        if (!duplicate){
            A[newSize] = A[i];
            newSize++;
        }
    }
    return newSize;
}

// (viii) Reverse Array 
void reverseArray(int A[], int n){
    int left = 0;
    int right = n - 1;
    int temp;
    while (left < right) {
        temp = A[left];
        A[left] = A[right];
        A[right] = temp;
        left++;
        right--;
    }
}


// (ix) Partition with Respect to Pivot 
void partitionArray(int A[], int n, int pivot)
{
    int left = 0;
    int right = n - 1;
    int temp;
    while (left <= right){
        while (left <= right && A[left] >= pivot){
            left++;
        }
        while (left <= right && A[right] < pivot) {
            right--;
        }

        if (left < right){
            temp = A[left];
            A[left] = A[right];
            A[right] = temp;
            left++;
            right--;
        }
    }
}

// Copy Array 
void copyArray(int source[], int destination[], int n){
    int i;
    for (i = 0; i < n; i++){
        destination[i] = source[i];
    }
}

// Display Array 
void displayArray(int A[], int n){
    int i;
    for (i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Main Function 
int main(){
    int A[100], B[100];
    int n, i;
    int pivot;
    int newSize;
    double mean;
    double median;
    double standardDeviation;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100){
        printf("Invalid array size.\n");
        return 0;
    }

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }

    // (i) Maximum 
    printf("Maximum element = %d\n",
           findMaximum(A, n));

    // (ii) First and Second Largest 
    findLargestAndSecondLargest(A, n);

    // (iii) Mean 
    mean = findMean(A, n);
    printf("Mean = %.2f\n", mean);

    // (iv) Median 
    copyArray(A, B, n);
    median = findMedian(B, n);
    printf("Median = %.2f\n", median);

    // (v) Standard Deviation 
    standardDeviation =findStandardDeviation(A, n);
    printf("Standard Deviation = %.2f\n",standardDeviation);

    // (vi) Mode 
    printf("Mode = %d\n", findMode(A, n));

    // (vii) Remove Duplicates 
    copyArray(A, B, n);
    newSize = removeDuplicates(B, n);
    printf("Array after removing duplicates:\n");
    displayArray(B, newSize);

    // (viii) Reverse 
    copyArray(A, B, n);
    reverseArray(B, n);
    printf("Reversed array:\n");
    displayArray(B, n);

    // (ix) Partition 
    printf("Enter pivot value: ");
    scanf("%d", &pivot);
    copyArray(A, B, n);
    partitionArray(B, n, pivot);
    printf("Array after partitioning:\n");
    displayArray(B, n);

    return 0;
}