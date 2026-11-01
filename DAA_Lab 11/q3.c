#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXL 10
#define MAXN 100000

typedef struct {
    char key[MAXL + 1];
    int head;
} Pattern;

typedef struct {
    int word;
    int next;
} Member;

Pattern *patterns;
Member *members;
int *hashTable;

int patternCount = 0;
int memberCount = 0;
int maxPatterns;
int hashSize;

uint64_t hashString(const char *s) {
    uint64_t h = 1469598103934665603ULL;

    while (*s) {
        h ^= (unsigned char)*s++;
        h *= 1099511628211ULL;
    }

    return h;
}

int getPattern(char *key, int create) {
    uint64_t h = hashString(key);
    int pos = (int)(h & (hashSize - 1));

    while (hashTable[pos] != 0) {
        int id = hashTable[pos] - 1;

        if (strcmp(patterns[id].key, key) == 0)
            return id;

        pos = (pos + 1) & (hashSize - 1);
    }

    if (!create)
        return -1;

    int id = patternCount++;

    strcpy(patterns[id].key, key);
    patterns[id].head = -1;

    hashTable[pos] = id + 1;

    return id;
}

void buildIndex(char words[][MAXL + 1], int M, int L) {
    char temp[MAXL + 1];

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < L; j++) {
            strcpy(temp, words[i]);
            temp[j] = '*';

            int id = getPattern(temp, 1);

            members[memberCount].word = i;
            members[memberCount].next = patterns[id].head;

            patterns[id].head = memberCount++;
        }
    }
}

/*
Returns:
- Minimum mutations if a meeting is found.
-1 if no path exists.
-2 if this BFS layer does not find a meeting.
*/

int expandLayer(
    int side,
    int L,
    int *distA,
    int *distB,
    int *queueA,
    int *queueB,
    int *headA,
    int *tailA,
    int *headB,
    int *tailB,
    int *usedA,
    int *usedB,
    char words[][MAXL + 1]
) {
    int *dist = side == 0 ? distA : distB;
    int *otherDist = side == 0 ? distB : distA;

    int *queue = side == 0 ? queueA : queueB;
    int *head = side == 0 ? headA : headB;
    int *tail = side == 0 ? tailA : tailB;

    int *used = side == 0 ? usedA : usedB;

    int layerEnd = *tail;
    char temp[MAXL + 1];

    for (int i = *head; i < layerEnd; i++) {
        int u = queue[i];

        if (otherDist[u] != -1)
            return dist[u] + otherDist[u];

        for (int j = 0; j < L; j++) {
            strcpy(temp, words[u]);
            temp[j] = '*';

            int pid = getPattern(temp, 0);

            if (pid == -1 || used[pid])
                continue;

            used[pid] = 1;

            for (int p = patterns[pid].head;
                 p != -1; p = members[p].next) {

                int v = members[p].word;

                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    queue[(*tail)++] = v;
                }

                if (otherDist[v] != -1)
                    return dist[v] + otherDist[v];
            }
        }
    }

    *head = layerEnd;

    return -2;
}

int bidirectionalBFS(
    int start,
    int target,
    int M,
    int L,
    char words[][MAXL + 1]
) {
    if (start == target)
        return 0;

    int *distA = malloc(M * sizeof(int));
    int *distB = malloc(M * sizeof(int));

    int *queueA = malloc(M * sizeof(int));
    int *queueB = malloc(M * sizeof(int));

    int *usedA = calloc(patternCount, sizeof(int));
    int *usedB = calloc(patternCount, sizeof(int));

    if (!distA || !distB || !queueA || !queueB ||
        !usedA || !usedB)
        return -1;

    for (int i = 0; i < M; i++) {
        distA[i] = -1;
        distB[i] = -1;
    }

    int headA = 0, tailA = 0;
    int headB = 0, tailB = 0;

    distA[start] = 0;
    distB[target] = 0;

    queueA[tailA++] = start;
    queueB[tailB++] = target;

    int answer = -1;

    while (headA < tailA && headB < tailB) {
        int result;

        // Expand the smaller current frontier.

        if (tailA - headA <= tailB - headB) {
            result = expandLayer(
                0, L, distA, distB,
                queueA, queueB,
                &headA, &tailA, &headB, &tailB,
                usedA, usedB, words
            );
        } else {
            result = expandLayer(
                1, L, distA, distB,
                queueA, queueB,
                &headA, &tailA, &headB, &tailB,
                usedA, usedB, words
            );
        }

        if (result != -2) {
            answer = result;
            break;
        }
    }

    free(distA);
    free(distB);
    free(queueA);
    free(queueB);
    free(usedA);
    free(usedB);

    return answer;
}

int findWord(char words[][MAXL + 1], int N, const char *key) {
    for (int i = 0; i < N; i++) {
        if (strcmp(words[i], key) == 0)
            return i;
    }

    return -1;
}

int main(void) {
    int N, L;

    printf("Enter N and L: ");

    if (scanf("%d %d", &N, &L) != 2 ||
        N <= 0 || N > MAXN || L <= 0 || L > MAXL)
        return 1;

    char (*words)[MAXL + 1] =
        calloc(N + 1, sizeof(*words));

    if (!words)
        return 1;

    printf("Enter dictionary words:\n");

    for (int i = 0; i < N; i++) {
        if (scanf("%10s", words[i]) != 1 ||
            strlen(words[i]) != (size_t)L) {
            printf("Invalid word length.\n");
            return 1;
        }

        for (int j = 0; j < L; j++) {
            if (words[i][j] < 'a' || words[i][j] > 'z') {
                printf("Invalid characters.\n");
                return 1;
            }
        }
    }

    char A[MAXL + 1], B[MAXL + 1];

    printf("Enter starting and target words: ");

    if (scanf("%10s %10s", A, B) != 2 ||
        strlen(A) != (size_t)L ||
        strlen(B) != (size_t)L) {
        printf("Invalid input.\n");
        return 1;
    }

    for (int j = 0; j < L; j++) {
        if (A[j] < 'a' || A[j] > 'z' ||
            B[j] < 'a' || B[j] > 'z') {
            printf("Invalid characters.\n");
            return 1;
        }
    }

    int target = findWord(words, N, B);

    if (target == -1) {
        printf("Target word not in dictionary.\n");
        free(words);
        return 0;
    }

    int start = findWord(words, N, A);
    int M = N;

    if (start == -1) {
        start = N;
        strcpy(words[M++], A);
    }

    maxPatterns = M * L;

    hashSize = 1;
    while (hashSize < 2 * maxPatterns)
        hashSize *= 2;

    patterns = malloc(maxPatterns * sizeof(Pattern));
    members = malloc(maxPatterns * sizeof(Member));
    hashTable = calloc(hashSize, sizeof(int));

    if (!patterns || !members || !hashTable)
        return 1;

    buildIndex(words, M, L);

    int result = bidirectionalBFS(
        start, target, M, L, words
    );

    if (result == -1)
        printf("No valid transformation sequence exists.\n");
    else
        printf("Minimum number of mutations: %d\n", result);

    free(words);
    free(patterns);
    free(members);
    free(hashTable);

    return 0;
}
