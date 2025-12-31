#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define INF 999999

void primMST(int graph[MAX][MAX], int n) {
    int parent[MAX];
    int key[MAX];
    bool inMST[MAX];
    
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        inMST[i] = false;
    }
    
    key[0] = 0;
    parent[0] = -1;
    
    for (int count = 0; count < n - 1; count++) {
        int min = INF, minIdx;
        
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                minIdx = v;
            }
        }
        
        int u = minIdx;
        inMST[u] = true;
        
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    
    printf("Prim's MST:\n");
    printf("Edge \tWeight\n");
    int totalWeight = 0;
    for (int i = 1; i < n; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("Total Weight: %d\n", totalWeight);
}

int main() {
    int n = 5;
    
    int graph[MAX][MAX] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    
    primMST(graph, n);
    
    return 0;
}
