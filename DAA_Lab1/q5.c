#include<stdio.h>
int Partition(int arr[],int n){
    int start=0,end=n-1,ans=-1;
    while(start<=end){
        int mid=start+(end-start)/2;
        if(arr[mid]==1){
            ans=mid;
            end=mid-1;
        }
        else
            start=mid+1;
    }
    return ans;
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int A[n];

    printf("Enter elements (0's followed by 1's):\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    int pos = Partition(A, n);

    if(pos == -1)
        printf("No transition found.\n");
    else
        printf("Transition occurs at position: %d\n", pos+1);

    return 0;
}