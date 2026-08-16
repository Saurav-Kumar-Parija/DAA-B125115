#include <stdio.h>
#include <stdlib.h>

// Binary search returning key comparison count
long long binary_search_cmp(int arr[], int l, int r, int x) {
    long long cmps = 0;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return ++cmps;

        cmps++;

        if (arr[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return cmps;
}

// Ternary search returning key comparison count
long long ternary_search_cmp(int arr[], int l, int r, int x) {
    long long cmps = 0;

    while (l <= r) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;

        if (arr[mid1] == x)
            return ++cmps;

        if (arr[mid2] == x)
            return ++cmps;

        cmps++;

        if (x < arr[mid1]) {
            r = mid1 - 1;
        } else {
            cmps++;

            if (x > arr[mid2]) {
                l = mid2 + 1;
            } else {
                l = mid1 + 1;
                r = mid2 - 1;
            }
        }
    }

    return cmps;
}

int main() {

    FILE *fp = fopen("search_comps.csv", "w");

    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "N,BinaryCmps,TernaryCmps\n");

    int start_n = 10000;
    int max_n = 5000000;
    int step = 100000;

    for (int n = start_n; n <= max_n; n += step) {

        int *arr = (int *)malloc(n * sizeof(int));

        if (arr == NULL) {
            printf("Memory allocation failed for N = %d\n", n);
            fclose(fp);
            return 1;
        }

        for (int i = 0; i < n; i++)
            arr[i] = i;

        int target = n + 1;

        long long bin_cmps =
            binary_search_cmp(arr, 0, n - 1, target);

        long long ter_cmps =
            ternary_search_cmp(arr, 0, n - 1, target);

        fprintf(fp, "%d,%lld,%lld\n",
                n, bin_cmps, ter_cmps);

        free(arr);
    }

    fclose(fp);

    printf("Data successfully exported to 'search_comps.csv'.\n");

    /* ------------------------------------------------
       Create GNUplot script
       ------------------------------------------------ */

    FILE *gp = fopen("plot.gnu", "w");

    if (!gp) {
        printf("Error creating GNUplot script!\n");
        return 1;
    }

    fprintf(gp,
        "set datafile separator ','\n"
        "set title 'Binary Search vs Ternary Search'\n"
        "set xlabel 'Input Size (N)'\n"
        "set ylabel 'Number of Key Comparisons'\n"
        "set grid\n"
        "set key left top\n"
        "set terminal pngcairo size 1000,700\n"
        "set output 'search_comparison.png'\n"
        "plot 'search_comps.csv' using 1:2 with linespoints "
        "title 'Binary Search' lw 2 pt 7, "
        "'search_comps.csv' using 1:3 with linespoints "
        "title 'Ternary Search' lw 2 pt 5\n"
    );

    fclose(gp);

    /* Run GNUplot */
    int result = system("gnuplot plot.gnu");

    if (result != 0) {
        printf("Error: GNUplot could not be executed.\n");
        printf("Make sure GNUplot is installed and added to PATH.\n");
        return 1;
    }

    printf("Graph successfully generated as 'search_comparison.png'.\n");

    return 0;
}