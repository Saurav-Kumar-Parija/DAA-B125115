#include <stdio.h>
#include <stdlib.h>

void buildOBST(int p[], int q[], int n,
               int **e, int **w, int **root) {

    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int length = 1; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            e[i][j] = 1000000000;

            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {

                int cost = e[i][r - 1]
                         + e[r + 1][j]
                         + w[i][j];

                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }
}

void printTree(int **root, int i, int j, int parent, char side) {

    if (i > j)
        return;

    int r = root[i][j];

    if (parent == 0)
        printf("Key %d is the root\n", r);
    else
        printf("Key %d is the %s child of Key %d\n",
               r,
               side == 'L' ? "left" : "right",
               parent);

    printTree(root, i, r - 1, r, 'L');
    printTree(root, r + 1, j, r, 'R');
}

int main() {
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of keys.\n");
        return 0;
    }

    int *p = malloc((n + 1) * sizeof(int));
    int *q = malloc((n + 1) * sizeof(int));

    int **e = malloc((n + 2) * sizeof(int *));
    int **w = malloc((n + 2) * sizeof(int *));
    int **root = malloc((n + 2) * sizeof(int *));

    if (p == NULL || q == NULL ||
        e == NULL || w == NULL || root == NULL) {

        printf("Memory allocation failed.\n");

        free(p);
        free(q);
        free(e);
        free(w);
        free(root);

        return 0;
    }

    for (int i = 0; i <= n + 1; i++) {
        e[i] = malloc((n + 1) * sizeof(int));
        w[i] = malloc((n + 1) * sizeof(int));
        root[i] = malloc((n + 1) * sizeof(int));

        if (e[i] == NULL || w[i] == NULL || root[i] == NULL) {
            printf("Memory allocation failed.\n");

            for (int k = 0; k <= i; k++) {
                free(e[k]);
                free(w[k]);
                free(root[k]);
            }

            free(e);
            free(w);
            free(root);
            free(p);
            free(q);

            return 0;
        }
    }

    printf("Enter successful search probabilities/frequencies p[1..n]:\n");

    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]);

    printf("Enter unsuccessful search probabilities/frequencies q[0..n]:\n");

    for (int i = 0; i <= n; i++)
        scanf("%d", &q[i]);

    buildOBST(p, q, n, e, w, root);

    printf("\nMinimum Expected Search Cost: %d\n", e[1][n]);

    printf("\nOptimal Binary Search Tree:\n");
    printTree(root, 1, n, 0, 'L');

    printf("\nRoot Table:\n");

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++)
            printf("root[%d][%d] = Key %d\n",
                   i, j, root[i][j]);
    }

    for (int i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
        free(root[i]);
    }

    free(e);
    free(w);
    free(root);
    free(p);
    free(q);

    return 0;
}