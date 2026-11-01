#include <stdio.h>
#include <stdlib.h>

#define INF -1

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

Node **graph;

void addEdge(int u, int v) {
    Node *a = malloc(sizeof(Node));
    Node *b = malloc(sizeof(Node));

    a->vertex = v;
    a->next = graph[u];
    graph[u] = a;

    b->vertex = u;
    b->next = graph[v];
    graph[v] = b;
}

void multiSourceBFS(int V, int K, int R, int hubs[]) {
    int *dist = malloc((V + 1) * sizeof(int));
    int *owner = malloc((V + 1) * sizeof(int));
    int *queue = malloc((V + 1) * sizeof(int));

    int front = 0, rear = 0;

    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        owner[i] = -1;
    }

    // Phase 1: Find minimum distance from any hub.

    for (int i = 0; i < K; i++) {
        int h = hubs[i];
        dist[h] = 0;
        queue[rear++] = h;
    }

    while (front < rear) {
        int u = queue[front++];

        if (dist[u] == R)
            continue;

        for (Node *p = graph[u]; p != NULL; p = p->next) {
            int v = p->vertex;

            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
        }
    }

    // Phase 2: Assign the smallest-index nearest hub.

    for (int i = 0; i < K; i++) {
        owner[hubs[i]] = i + 1;
    }

    for (int i = 0; i < rear; i++) {
        int u = queue[i];

        if (dist[u] == 0)
            continue;

        int bestOwner = -1;

        for (Node *p = graph[u]; p != NULL; p = p->next) {
            int v = p->vertex;

            if (dist[v] == dist[u] - 1) {
                if (bestOwner == -1 || owner[v] < bestOwner)
                    bestOwner = owner[v];
            }
        }

        owner[u] = bestOwner;
    }

    printf("\nVertex\tOwner\tDistance\n");

    for (int i = 1; i <= V; i++) {
        if (dist[i] == INF) {
            printf("%d\t-1\t-1\n", i);
        } else {
            printf("%d\t%d\t%d\n", i, owner[i], dist[i]);
        }
    }

    free(dist);
    free(owner);
    free(queue);
}

int main(void) {
    int V, E, K, R;

    printf("Enter number of vertices and edges: ");

    if (scanf("%d %d", &V, &E) != 2 || V <= 0 || E < 0)
        return 1;

    graph = calloc(V + 1, sizeof(Node *));

    if (graph == NULL)
        return 1;

    printf("Enter undirected edges (u v):\n");

    for (int i = 0; i < E; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > V || v < 1 || v > V) {
            printf("Invalid edge.\n");
            return 1;
        }

        addEdge(u, v);
    }

    printf("Enter number of hubs K and radius R: ");

    if (scanf("%d %d", &K, &R) != 2 ||
        K < 1 || K > V || R < 0) {
        printf("Invalid hub count or radius.\n");
        return 1;
    }

    int *hubs = malloc(K * sizeof(int));
    int *used = calloc(V + 1, sizeof(int));

    if (hubs == NULL || used == NULL)
        return 1;

    printf("Enter %d hub vertices in index order:\n", K);

    for (int i = 0; i < K; i++) {
        if (scanf("%d", &hubs[i]) != 1 ||
            hubs[i] < 1 || hubs[i] > V || used[hubs[i]]) {
            printf("Invalid or duplicate hub.\n");
            return 1;
        }

        used[hubs[i]] = 1;
    }

    multiSourceBFS(V, K, R, hubs);

    for (int i = 1; i <= V; i++) {
        Node *p = graph[i];

        while (p != NULL) {
            Node *temp = p;
            p = p->next;
            free(temp);
        }
    }

    free(graph);
    free(hubs);
    free(used);

    return 0;
}
