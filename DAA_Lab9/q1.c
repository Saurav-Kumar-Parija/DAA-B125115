#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double value;
    double weight;
    double decay;
    double density;
} Item;

int compare(const void *a, const void *b) {
    const Item *x = (const Item *)a;
    const Item *y = (const Item *)b;

    if (x->decay < y->decay)
        return 1;

    if (x->decay > y->decay)
        return -1;

    return 0;
}

double minimum3(double a, double b, double c) {
    double result = a;

    if (b < result)
        result = b;

    if (c < result)
        result = c;

    return result;
}

int main() {
    int n;
    double W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item items[n];

    printf("Enter value, weight and decay rate:\n");

    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;

        printf("Item %d: ", i + 1);
        scanf("%lf %lf %lf",
              &items[i].value,
              &items[i].weight,
              &items[i].decay);

        items[i].density =
            items[i].value / items[i].weight;
    }

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    qsort(items, n, sizeof(Item), compare);

    double time = 0.0;
    double remaining = W;
    double totalValue = 0.0;

    printf("\nOptimal Scheduling Order:\n");

    for (int i = 0; i < n; i++) {
        printf("Item %d (Decay Rate = %.2f)\n",
               items[i].id,
               items[i].decay);
    }

    printf("\nSelection Details:\n");
    printf("Item\tAmount\tFraction\tStart Time\t");
    printf("End Time\tValue\n");

    for (int i = 0; i < n && remaining > 0; i++) {
        double currentDensity;
        double usefulAmount;
        double amount;
        double value;

        currentDensity =
            items[i].density -
            items[i].decay * time;

        if (currentDensity <= 0)
            continue;

        usefulAmount =
            items[i].density / items[i].decay - time;

        amount = minimum3(
            items[i].weight,
            remaining,
            usefulAmount
        );

        if (amount <= 0)
            continue;

        value =
            amount * currentDensity
            - (items[i].decay * amount * amount) / 2.0;

        printf("%d\t%.2f\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",
               items[i].id,
               amount,
               amount / items[i].weight,
               time,
               time + amount,
               value);

        totalValue += value;
        time += amount;
        remaining -= amount;
    }

    printf("\nMaximum Total Value = %.2f\n", totalValue);
    printf("Used Capacity = %.2f\n", W - remaining);
    printf("Unused Capacity = %.2f\n", remaining);

    return 0;
}