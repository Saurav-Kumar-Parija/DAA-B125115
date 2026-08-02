#include <stdio.h>
void merge(int A[], int l, int m, int r){
    int i = l, j = m + 1, k = 0;
    int temp[r - l + 1];

    while(i <= m && j <= r){
        if(A[i] <= A[j])
            temp[k++] = A[i++];
        else
            temp[k++] = A[j++];
    }

    while(i <= m)
        temp[k++] = A[i++];

    while(j <= r)
        temp[k++] = A[j++];

    for(i = l, k = 0; i <= r; i++, k++)
        A[i] = temp[k];
}

void mergeSort(int A[], int l, int r){
    if(l < r){
        int m = (l + r) / 2;
        mergeSort(A, l, m);
        mergeSort(A, m + 1, r);
        merge(A, l, m, r);
    }
}

int main(){
    int n, i;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int A[n];

    printf("Enter %d random numbers:\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", &A[i]);
// Sorting
    mergeSort(A, 0, n - 1);
//Scanning
    for(i = 0; i < n - 1; i++){
        if(A[i] == A[i + 1]){
            printf("Duplicate element found.\n");
            return 0; 
        }
    }
    printf("All elements are unique.\n");
}