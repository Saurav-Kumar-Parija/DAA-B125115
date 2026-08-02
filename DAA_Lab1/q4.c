#include<stdio.h>
#include<math.h>
#define MAX_DISKS 10
#define HEIGHT 20

void TOH(int n,char l,char m,char r){
    if(n==1){
        printf("Move disk 1 from %c to %c\n",l,r);
        return;
    }
    TOH(n-1,l,r,m);
    printf("Move disk %d from %c to %c\n",n,l,r);
    TOH(n-1,m,l,r);
}
int main(){
    int n, i;
    printf("Enter number of disks: ");
    scanf("%d", &n);

    printf("\nSteps to solve Tower of Hanoi:\n\n");
    TOH(n, 'A', 'B', 'C');

    printf("\nTotal Moves Required = %.0lf\n", pow(2, n) - 1);

    //Graph Plotting
    int moves[MAX_DISKS + 1];
    int maxMoves = pow(2,MAX_DISKS) - 1;

    // Calculating Moves
    for (int i = 1; i <= MAX_DISKS; i++)
        moves[i] =pow(2,i) - 1;

    printf("\nTower of Hanoi\n");
    printf("Cartesian Graph\n\n");

    // Drawing graph
    for (int row = HEIGHT; row >= 0; row--)
    {
        int level = (maxMoves * row) / HEIGHT;

        printf("%4d |", level);
        
        for (int col = 1; col <= MAX_DISKS; col++)
        {
            if (moves[col] >= level &&
                moves[col] < level + maxMoves / HEIGHT)
                printf("   *");
            else
                printf("    ");
        }

        printf("\n");
    }

    printf("     +-------------------------------------------->\n");
    printf("       ");

    for (int i = 1; i <= MAX_DISKS; i++)
        printf("%4d", i);

    printf("\n");
    printf("             Number of Disks\n\n");

    printf("Moves:\n");
    for (int i = 1; i <= MAX_DISKS; i++)
        printf("n = %2d   Moves = %4d\n", i, moves[i]);
}
