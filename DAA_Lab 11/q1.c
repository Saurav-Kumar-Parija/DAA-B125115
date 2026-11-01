
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (LLONG_MAX / 4)

typedef struct Edge {
    int to, weight;
    struct Edge *next;
} Edge;

typedef struct {
    int vertex, parity;
} State;

Edge **graph;

void addEdge(int u, int v, int w) {
    Edge *e = malloc(sizeof(Edge));
    e->to = v;
    e->weight = w;
    e->next = graph[u];
    graph[u] = e;
}

void zeroOneBFS(int V, int S, long long C) {
    long long (*dist)[2] = malloc((V + 1) * sizeof(*dist));

    int capacity = 4 * (V + 1) + 4;
    State *deque = malloc(capacity * sizeof(State));
    int front = capacity / 2;
    int back = front;

    for (int i = 1; i <= V; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    dist[S][0] = 0;
    deque[back++] = (State){S, 0};

    while (front < back) {
        State cur = deque[front++];
        int u = cur.vertex;
        int parity = cur.parity;

        for (Edge *e = graph[u]; e != NULL; e = e->next) {
            int v = e->to;
            int w = e->weight;
            int nextParity = parity ^ w;
            long long newDist = dist[u][parity] + w;

            if (newDist < dist[v][nextParity]) {
                dist[v][nextParity] = newDist;

                if (w == 0)
                    deque[--front] = (State){v, nextParity};
                else
                    deque[back++] = (State){v, nextParity};
            }
        }
    }

    printf("\nMinimum effective costs:\n");

    for (int v = 1; v <= V; v++) {
        if (dist[v][0] == INF && dist[v][1] == INF) {
            printf("Vertex %d: Unreachable\n", v);
            continue;
        }

        long long evenCost = dist[v][0];
        long long oddCost = dist[v][1] == INF
                                ? INF : dist[v][1] + C;

        long long answer = evenCost < oddCost
                               ? evenCost : oddCost;

        printf("Vertex %d: %lld\n", v, answer);
    }

    free(dist);
    free(deque);
}

int main(void) {
    int V, E, S;
    long long C;

    printf("Enter V, E, source S and penalty C: ");
    if (scanf("%d %d %d %lld", &V, &E, &S, &C) != 4)
        return 1;

    if (V <= 0 || E < 0 || S < 1 || S > V || C < 0)
        return 1;

    graph = calloc(V + 1, sizeof(Edge *));

    if (graph == NULL)
        return 1;

    printf("Enter directed edges (u v w):\n");

    for (int i = 0; i < E; i++) {
        int u, v, w;

        if (scanf("%d %d %d", &u, &v, &w) != 3 ||
            u < 1 || u > V || v < 1 || v > V ||
            (w != 0 && w != 1)) {
            printf("Invalid edge input.\n");
            return 1;
        }

        addEdge(u, v, w);
    }

    zeroOneBFS(V, S, C);

    for (int u = 1; u <= V; u++) {
        Edge *e = graph[u];

        while (e != NULL) {
            Edge *temp = e;
            e = e->next;
            free(temp);
        }
    }

    free(graph);
    return 0;
}
