#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define STEP 10
#define ROWS 10

int bubbleOptimized(int arr[],int n){
    int comparisions=0;
    for(int i=0;i<n-1;i++){
        int swapped=0;
        for(int j=0;j<n-i-1;j++){
            comparisions++;
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                swapped=1;
            }
        }
        if(!swapped)
        break;
    }
return comparisions;
}

int bubbleNormal(int arr[],int n){
    int comparisions=0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            comparisions++;
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }   
}
return comparisions;
}

int main(){
    srand(time(NULL));

    int size[10];
    int opt[10];
    int normal[10];

    int index = 0;
    int maxComp = 0;

    printf("Array Size\tOptimized\tNormal\n");
    printf("-----------------------------------------\n");

    for(int n = 10; n <= MAX; n += STEP)
    {
        int a[MAX], b[MAX];

        for(int i = 0; i < n; i++)
        {
            a[i] = rand() % 1000;
            b[i] = a[i];
        }

        opt[index] = bubbleOptimized(a, n);
        normal[index] = bubbleNormal(b, n);
        size[index] = n;

        if(normal[index] > maxComp)
            maxComp = normal[index];

        printf("%3d\t\t%5d\t\t%5d\n",
               n, opt[index], normal[index]);

        index++;
    }

    printf("\n\nASCII GRAPH\n");
    printf("Y-axis : Comparisons\n");
    printf("X-axis : Array Size\n\n");

    for(int r = ROWS; r >= 0; r--)
    {
        int level = (maxComp * r) / ROWS;

        printf("%4d | ", level);

        for(int i = 0; i < index; i++)
        {
            char ch = ' ';

            if(opt[i] >= level && opt[i] < level + maxComp / ROWS)
                ch = 'O';

            if(normal[i] >= level && normal[i] < level + maxComp / ROWS)
            {
                if(ch == 'O')
                    ch = 'X';
                else
                    ch = 'N';
            }

            printf(" %c ", ch);
        }

        printf("\n");
    }

    printf("     +---------------------------------------> Array Size\n");
    printf("       ");

    for(int i = 0; i < index; i++)
        printf("%2d ", size[i]);

    printf("\n\n");
    printf("O = Optimized Bubble Sort\n");
    printf("N = Normal Bubble Sort\n");
    printf("X = Both overlap\n");

    return 0;
}