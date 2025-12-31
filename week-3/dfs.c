#include <stdio.h>
#include <stdbool.h>

#define MAX 10

void DFSUtil(int graph[MAX][MAX], int n, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);
    
    for (int i = 0; i < n; i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            DFSUtil(graph, n, i, visited);
        }
    }
}

void DFS(int graph[MAX][MAX], int n, int start) {
    bool visited[MAX] = {false};
    printf("DFS Traversal: ");
    DFSUtil(graph, n, start, visited);
    printf("\n");
}

int main() {
    int n = 5;
    
    int graph[MAX][MAX] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };
    
    DFS(graph, n, 0);
    
    return 0;
}
