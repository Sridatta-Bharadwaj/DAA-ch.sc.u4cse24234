#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int parent, rank;
} Subset;

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compare(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

void kruskalMST(Edge edges[], int e, int n) {
    qsort(edges, e, sizeof(Edge), compare);
    
    Subset* subsets = (Subset*)malloc(n * sizeof(Subset));
    for (int v = 0; v < n; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    printf("Kruskal's MST:\n");
    printf("Edge \tWeight\n");
    
    int edgeCount = 0, totalWeight = 0, i = 0;
    
    while (edgeCount < n - 1 && i < e) {
        Edge nextEdge = edges[i++];
        
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);
        
        if (x != y) {
            printf("%d - %d \t%d\n", nextEdge.src, nextEdge.dest, nextEdge.weight);
            totalWeight += nextEdge.weight;
            unionSets(subsets, x, y);
            edgeCount++;
        }
    }
    
    printf("Total Weight: %d\n", totalWeight);
    free(subsets);
}

int main() {
    int n = 5;
    
    Edge edges[] = {
        {0, 1, 2}, {1, 2, 3}, {1, 4, 5}, {0, 3, 6},
        {2, 4, 7}, {1, 3, 8}, {3, 4, 9}
    };
    int numEdges = 7;
    
    kruskalMST(edges, numEdges, n);
    
    return 0;
}
