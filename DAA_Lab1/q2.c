#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POINTS 7
#define ROWS 11     // 0.0 to 1.0

int main() {
    int tosses[POINTS] = {10, 50, 100, 500, 1000, 5000, 10000};
    double fair[POINTS], biased[POINTS];

    srand(time(NULL));

    // Simulate
    for(int i = 0; i < POINTS; i++) {
        int N = tosses[i];
        int fh = 0, bh = 0;

        for(int j = 0; j < N; j++)
            if(rand() % 2) fh++;
//Assuming Bias of 70%
        for(int j = 0; j < N; j++) {
            double r = (double)rand() / RAND_MAX;
            if(r < 0.7) bh++;
        }

        fair[i] = (double)fh / N;
        biased[i] = (double)bh / N;
    }

    printf("\nProbability\n\n");

    // Draw graph
    for(int r = ROWS - 1; r >= 0; r--) {

        double level = r / 10.0;
        printf("%.1f |", level);

        for(int c = 0; c < POINTS; c++) {

            char ch = ' ';

            if(fair[c] >= level && fair[c] < level + 0.1)
                ch = 'F';

            if(biased[c] >= level && biased[c] < level + 0.1)
                ch = (ch == 'F') ? 'X' : 'B';

            printf("    %c", ch);
        }

        printf("\n");
    }

    printf("    +-------------------------------------------\n");
    printf("      10   50  100  500 1000 5000 10000\n");
    printf("             Number of Tosses\n\n");

    printf("F = Fair Coin\n");
    printf("B = Biased Coin\n");
    printf("X = Both overlap\n");

    printf("\nExperimental Probabilities\n");
    printf("----------------------------------------\n");
    printf("Tosses\tFair\tBiased\n");

    for(int i = 0; i < POINTS; i++)
        printf("%5d\t%.3f\t%.3f\n", tosses[i], fair[i], biased[i]);

    return 0;
}