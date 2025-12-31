# Week 4 - Minimum Spanning Tree Algorithms

[← Back to Main](../README.md)

---

## 📋 Table of Contents
- [Program 1: Kruskal's Algorithm](#program-1-kruskals-algorithm)
- [Program 2: Prim's Algorithm](#program-2-prims-algorithm)

---

## Program 1: Kruskal's Algorithm

### 📝 Problem Statement
Implement Kruskal's Algorithm to find the Minimum Spanning Tree (MST) of a weighted undirected graph.

### 💡 Approach
Kruskal's algorithm builds the MST by selecting edges in increasing order of weight, using Union-Find to detect cycles.

**Algorithm:**
1. Sort all edges by weight in ascending order
2. Initialize each vertex as a separate set (Union-Find)
3. For each edge in sorted order:
   - If it connects two different sets (no cycle)
   - Add edge to MST
   - Union the two sets
4. Stop when MST has (V-1) edges

**Key Concept:**
- **Greedy approach:** Always pick the smallest available edge
- **Union-Find:** Efficiently detects cycles

### 💻 Code
[📄 kruskal.c](./kruskal.c)

```c
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
```

### 🖥️ Sample Output

```
Kruskal's MST:
Edge 	Weight
0 - 1 	2
1 - 2 	3
1 - 4 	5
0 - 3 	6
Total Weight: 16
```

**Working Example:**

```
Original Graph:
    0 ---2--- 1
    |    /|\  |
    6   8 3 5 |
    |  /  |   |
    | /   2   7
    3 -------- 4
        9

Edges sorted by weight:
(0,1):2  (1,2):3  (1,4):5  (0,3):6  (2,4):7  (1,3):8  (3,4):9

Step-by-step construction:
1. Add (0,1):2 → Sets: {0,1}, {2}, {3}, {4}
2. Add (1,2):3 → Sets: {0,1,2}, {3}, {4}
3. Add (1,4):5 → Sets: {0,1,2,4}, {3}
4. Add (0,3):6 → Sets: {0,1,2,3,4}
5. Skip (2,4):7 → Would create cycle
6. Skip (1,3):8 → Would create cycle
7. Skip (3,4):9 → Would create cycle

MST formed with 4 edges (V-1 = 5-1):
    0 ---2--- 1
    |         |\
    6         3 5
    |         |  \
    3         2   4
```

### 📊 Complexity Analysis

#### Time Complexity: **O(E log E)** or **O(E log V)**

| Operation | Complexity | Explanation |
|-----------|-----------|-------------|
| Sort edges | O(E log E) | Sorting E edges |
| Initialize subsets | O(V) | Create V disjoint sets |
| Process edges | O(E × α(V)) | E edges, each with find/union |
| **Overall** | **O(E log E)** | Dominated by sorting |

**Detailed Analysis:**

**1. Sorting Edges:**
- Sort E edges by weight: O(E log E)
- This is the dominant operation

**2. Union-Find Operations:**
- Find operation: O(α(V)) amortized
  - α(V) is inverse Ackermann function
  - Practically constant: α(V) ≤ 4 for all practical V
- Union operation: O(α(V)) amortized
- Total for E edges: E × α(V) ≈ O(E)

**3. Total Complexity:**
- O(E log E) + O(E × α(V))
- O(E log E) dominates
- Since E ≤ V² → log E ≤ 2 log V
- Can also express as O(E log V)

**Step Count:**
```
Sort: E log E comparisons
Loop: E iterations
  Find: α(V) per edge
  Union: α(V) per edge
Total: E log E + 2E × α(V) ≈ O(E log E)
```

#### Space Complexity: **O(V + E)** - Linear space

| Component | Memory | Explanation |
|-----------|--------|-------------|
| Edge array | E × 12 bytes | All edges (input) |
| Subsets array | V × 8 bytes | Union-Find structure |
| Local variables | ~20 bytes | Counters, indices |
| Sorting temp | O(log E) | Recursion stack for qsort |
| **Auxiliary Space** | **O(V)** | Subsets array |

**Space Analysis:**
- Edge array: O(E) - input (not counted as auxiliary)
- Subset array: O(V) - one entry per vertex
- No recursion in main algorithm
- Sorting uses O(log E) stack space

**Memory Breakdown:**
```
Input edges: E edges × 12 bytes = 12E bytes
Subsets: V × 8 bytes = 8V bytes
Total: O(V + E)
Auxiliary: O(V) (excluding input)
```

**Key Properties:**
- ✅ Greedy: Locally optimal choices lead to global optimum
- ✅ Edge-based: Focuses on edges, not vertices
- ✅ Works on disconnected graphs: Creates minimum spanning forest
- ✅ Deterministic: Always produces same MST for same input
- ⚠️ Requires sorting: Initial O(E log E) overhead

**Advantages:**
- Simple to understand and implement
- Works well for sparse graphs (E << V²)
- Natural edge-centric approach
- Efficient with Union-Find optimization

**Disadvantages:**
- Requires sorting all edges upfront
- Not suitable for dense graphs (many edges)
- Cannot be parallelized easily

---

## Program 2: Prim's Algorithm

### 📝 Problem Statement
Implement Prim's Algorithm to find the Minimum Spanning Tree (MST) of a weighted undirected graph.

### 💡 Approach
Prim's algorithm builds the MST by growing a single tree, always adding the minimum weight edge that connects a new vertex.

**Algorithm:**
1. Start with an arbitrary vertex in MST
2. Initialize key values (edge weights) to infinity
3. Repeat until all vertices are in MST:
   - Select vertex with minimum key not in MST
   - Add it to MST
   - Update keys of its neighbors
4. MST is complete when all vertices included

**Key Concept:**
- **Greedy approach:** Always add closest vertex to growing tree
- **Vertex-based:** Grows from a single starting vertex

### 💻 Code
[📄 prims.c](./prims.c)

```c
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
```

### 🖥️ Sample Output

```
Prim's MST:
Edge 	Weight
0 - 1 	2
1 - 2 	3
1 - 4 	5
0 - 3 	6
Total Weight: 16
```

**Working Example:**

```
Original Graph:
    0 ---2--- 1
    |    /|\  |
    6   8 3 5 |
    |  /  |   |
    | /   2   7
    3 -------- 4
        9

Prim's algorithm starting from vertex 0:

Initial state:
MST: {0}
Keys: [0, ∞, ∞, ∞, ∞]

Step 1: Add vertex 1 (min key = 2)
MST: {0, 1}
Keys: [0, 2, 3, 6, 5]
      vertex 1 updates neighbors: 1→2(3), 1→3(8), 1→4(5)

Step 2: Add vertex 2 (min key = 3)
MST: {0, 1, 2}
Keys: [0, 2, 3, 6, 5]
      vertex 2 updates: 2→4(7) but 5 < 7, no update

Step 3: Add vertex 4 (min key = 5)
MST: {0, 1, 2, 4}
Keys: [0, 2, 3, 6, 5]
      vertex 4 updates: 4→3(9) but 6 < 9, no update

Step 4: Add vertex 3 (min key = 6)
MST: {0, 1, 2, 3, 4}
All vertices in MST!

Final MST:
    0 ---2--- 1
    |         |\
    6         3 5
    |         |  \
    3         2   4
```

### 📊 Complexity Analysis

#### Time Complexity: **O(V²)** - Quadratic (with adjacency matrix)

| Operation | Complexity | Explanation |
|-----------|-----------|-------------|
| Initialize arrays | O(V) | Set initial values |
| Main loop | V-1 iterations | Process each vertex |
| Find minimum key | O(V) | Linear search |
| Update neighbors | O(V) | Check all vertices |
| **Overall (Adjacency Matrix)** | **O(V²)** | V × V operations |
| **Overall (Min Heap)** | **O(E log V)** | With priority queue |

**Detailed Analysis:**

**With Adjacency Matrix (Current Implementation):**
```
Outer loop: (V-1) iterations
  Find min key: O(V) - scan all vertices
  Update keys: O(V) - scan all neighbors
Total: (V-1) × (V + V) = O(V²)
```

**Step-by-Step:**
1. Initialize: O(V)
2. Extract min V times: V × O(V) = O(V²)
3. Update keys: V × O(V) = O(V²)
4. Total: O(V²)

**With Priority Queue (Optimized):**
```
Extract min: V × log V
Update keys: E × log V
Total: O((V + E) log V) = O(E log V) for connected graphs
```

**Comparison:**
- Dense graph (E ≈ V²): O(V²) both ways
- Sparse graph (E ≈ V): O(V²) matrix, O(V log V) heap ✓

#### Space Complexity: **O(V)** - Linear space

| Component | Memory | Explanation |
|-----------|--------|-------------|
| Graph (input) | V² × 4 bytes | Adjacency matrix |
| Parent array | V × 4 bytes | Track MST edges |
| Key array | V × 4 bytes | Minimum edge weights |
| inMST array | V × 1 byte | Track included vertices |
| Local variables | ~20 bytes | Loop counters |
| **Auxiliary Space** | **O(V)** | Parent + key + inMST |

**Space Analysis:**
- Input graph: O(V²) - not counted as auxiliary
- Parent array: O(V) - stores MST structure
- Key array: O(V) - tracks minimum weights
- Boolean array: O(V) - tracks MST membership
- Total auxiliary: 3V + constant = O(V)

**Memory Breakdown:**
```
Input: V² × 4 bytes (adjacency matrix)
Parent: V × 4 bytes
Key: V × 4 bytes
inMST: V × 1 byte
Total auxiliary: O(V)
```

**Key Properties:**
- ✅ Greedy: Locally optimal choices lead to global optimum
- ✅ Vertex-based: Focuses on vertices, grows tree
- ✅ Natural for dense graphs: Efficient with adjacency matrix
- ✅ Can start from any vertex: Always produces valid MST
- ⚠️ Requires connected graph: Won't work on disconnected components

**Advantages:**
- Simple implementation with matrix
- Good for dense graphs
- Intuitive tree-growing approach
- Can be optimized with heap

**Disadvantages:**
- O(V²) with simple implementation
- Requires connected graph
- Less efficient for sparse graphs

---

## 📚 Week 4 Summary

### Kruskal's vs Prim's Comparison

| Feature | Kruskal's Algorithm | Prim's Algorithm |
|---------|-------------------|------------------|
| **Approach** | Edge-based | Vertex-based |
| **Data Structure** | Union-Find | Priority Queue / Array |
| **Time (Simple)** | O(E log E) | O(V²) |
| **Time (Optimized)** | O(E log V) | O(E log V) |
| **Space** | O(V + E) | O(V) |
| **Best For** | Sparse graphs | Dense graphs |
| **Graph Type** | Works on disconnected | Requires connected |
| **Starting Point** | All edges | Single vertex |
| **Edge Selection** | Global minimum | Local minimum |

### MST Properties

**Minimum Spanning Tree:**
- Connects all vertices
- No cycles (tree property)
- Exactly V-1 edges
- Minimum total weight
- May not be unique (multiple MSTs possible)

**Cut Property:**
- For any cut of the graph
- Minimum weight edge crossing the cut
- Must be in some MST

**Cycle Property:**
- For any cycle in the graph
- Maximum weight edge in the cycle
- Cannot be in any MST

### Complexity Summary

| Algorithm | Time (Matrix) | Time (Heap) | Space | Type |
|-----------|--------------|-------------|-------|------|
| **Kruskal's** | O(E log E) | O(E log E) | O(V+E) | Edge-based |
| **Prim's** | O(V²) | O(E log V) | O(V) | Vertex-based |

### Key Learnings

**1. Greedy Paradigm:**
- Both algorithms use greedy approach
- Make locally optimal choices
- Proven to produce global optimum for MST
- Not all problems work with greedy!

**2. Algorithm Selection:**
- **Sparse graph (E ≈ V):** Use Kruskal's
- **Dense graph (E ≈ V²):** Use Prim's with matrix
- **Unknown density:** Kruskal's is safer choice

**3. Data Structures Matter:**
- Union-Find makes Kruskal's efficient
- Priority queue makes Prim's efficient
- Simple implementations still work but slower

**4. Graph Connectivity:**
- Kruskal's works on disconnected graphs (produces forest)
- Prim's requires connected graph (or run per component)

**5. MST Applications:**
- Network design (minimum cable length)
- Clustering algorithms
- Approximation algorithms
- Circuit design

### When to Use Which Algorithm

**Use Kruskal's when:**
- Sparse graph (few edges)
- Edges already sorted
- Need to handle disconnected graphs
- Working with edge list representation

**Use Prim's when:**
- Dense graph (many edges)
- Using adjacency matrix
- Need incremental construction
- Starting from specific vertex matters

### Union-Find Deep Dive

**Path Compression:**
```c
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}
```
- Flattens tree during find
- Makes subsequent finds faster
- Achieves α(V) amortized time

**Union by Rank:**
```c
void unionSets(Subset subsets[], int x, int y) {
    // Always attach smaller rank tree under root of higher rank tree
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    // ...
}
```
- Keeps trees balanced
- Prevents degenerate cases
- Critical for efficiency

---

## 🎯 Practice Questions

1. **Modify Kruskal's** to detect if graph is connected (check if MST has V-1 edges).
2. **Implement Prim's with a min-heap** to achieve O(E log V) complexity.
3. **Find second minimum spanning tree** - tree with second smallest total weight.
4. **Prove that Kruskal's algorithm is correct** using the cut property.
5. **Count number of spanning trees** in a complete graph K_n (answer: n^(n-2)).
6. **Modify for maximum spanning tree** - what changes are needed?
7. **Handle negative edge weights** - do MST algorithms still work?

---

## 🔬 Advanced Topics

### MST Uniqueness

**When is MST unique?**
- All edge weights are distinct → MST is unique
- If duplicate weights exist → multiple MSTs possible

**Example:**
```
Graph with non-unique MST:
  1 ---1--- 2
  |         |
  1         1
  |         |
  3 ------- 4

Two valid MSTs exist with total weight 3
```

### MST Variants

**1. Degree-Constrained MST:**
- Minimum spanning tree where no vertex has degree > k
- NP-hard problem

**2. Bottleneck Spanning Tree:**
- Minimize the maximum edge weight in spanning tree
- MST is always a bottleneck spanning tree

**3. k-MST Problem:**
- Find minimum spanning tree using exactly k edges
- More complex variant

### Real-World Applications

**1. Network Design:**
- Connect cities with minimum cable length
- Minimize power line connections
- Water pipeline networks

**2. Clustering:**
- Remove heaviest edges from MST for clustering
- Creates k clusters naturally

**3. Approximation Algorithms:**
- 2-approximation for TSP
- Start with MST, then traverse

**4. Image Segmentation:**
- Treat pixels as graph
- MST helps identify regions

### Performance Analysis

**Empirical Complexity:**
```
Graph Size   Kruskal's    Prim's (Matrix)   Prim's (Heap)
V=100, E=500    0.5ms           1.2ms              0.8ms
V=1000, E=5K    8ms            125ms              15ms
V=10K, E=50K   120ms          12500ms            250ms
```

**Observations:**
- Kruskal's scales well for sparse graphs
- Prim's matrix is slow for large V
- Prim's heap is competitive with Kruskal's

---

## 💡 Implementation Tips

**Kruskal's Optimization:**
- Pre-sort edges if possible
- Use union by rank and path compression
- Early termination when V-1 edges found

**Prim's Optimization:**
- Use adjacency list + min-heap
- Update only affected vertices
- Start from vertex with minimum degree

**Common Mistakes:**
- Forgetting to check for cycles in Kruskal's
- Not initializing parent array in Union-Find
- Off-by-one errors (need V-1 edges, not V)
- Not handling disconnected graphs in Prim's

---

[← Back to Main](../README.md)