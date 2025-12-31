# Week 3 - Graph Traversal Algorithms

[← Back to Main](../README.md)

---

## 📋 Table of Contents
- [Program 1: Breadth-First Search (BFS)](#program-1-breadth-first-search-bfs)
- [Program 2: Depth-First Search (DFS)](#program-2-depth-first-search-dfs)

---

## Program 1: Breadth-First Search (BFS)

### 📝 Problem Statement
Implement Breadth-First Search (BFS) algorithm to traverse a graph starting from a given vertex.

### 💡 Approach
BFS explores a graph level by level using a queue. It visits all neighbors of a vertex before moving to the next level.

**Algorithm:**
1. Mark the starting vertex as visited and enqueue it
2. While queue is not empty:
   - Dequeue a vertex and process it
   - Enqueue all unvisited neighbors
3. Repeat until all reachable vertices are visited

**Key Characteristics:**
- Uses a queue (FIFO) data structure
- Explores vertices level by level
- Finds shortest path in unweighted graphs

### 💻 Code
[📄 bfs.c](./bfs.c)

```c
#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int val) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = val;
}

int dequeue(Queue* q) {
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

void BFS(int graph[MAX][MAX], int n, int start) {
    bool visited[MAX] = {false};
    Queue q;
    initQueue(&q);
    
    visited[start] = true;
    enqueue(&q, start);
    
    printf("BFS Traversal: ");
    
    while (!isEmpty(&q)) {
        int curr = dequeue(&q);
        printf("%d ", curr);
        
        for (int i = 0; i < n; i++) {
            if (graph[curr][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }
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
    
    BFS(graph, n, 0);
    
    return 0;
}
```

### 🖥️ Sample Output

```
BFS Traversal: 0 1 2 3 4
```

**Working Example:**

```
Graph Structure:
    0 --- 1
    |     |\ 
    |     | \
    2 --- 4  3

Adjacency Matrix:
    0 1 2 3 4
0 [ 0 1 1 0 0 ]
1 [ 1 0 0 1 1 ]
2 [ 1 0 0 0 1 ]
3 [ 0 1 0 0 1 ]
4 [ 0 1 1 1 0 ]

BFS from vertex 0:
Level 0: [0]
Level 1: [1, 2]      → Neighbors of 0
Level 2: [3, 4]      → Neighbors of 1 and 2
Traversal: 0 → 1 → 2 → 3 → 4
```

### 📊 Complexity Analysis

#### Time Complexity: **O(V + E)** - Linear in graph size

| Operation | Complexity | Explanation |
|-----------|-----------|-------------|
| Initialize visited array | O(V) | Visit each vertex once |
| Traverse adjacency matrix | O(V²) | Check all edges |
| Queue operations | O(V) | Each vertex enqueued/dequeued once |
| **Overall (Adjacency Matrix)** | **O(V²)** | Dominated by matrix traversal |
| **Overall (Adjacency List)** | **O(V+E)** | More efficient representation |

**Detailed Analysis:**
- Each vertex is visited exactly once: O(V)
- For each vertex, we check all its neighbors
- With adjacency matrix: O(V) checks per vertex = O(V²) total
- With adjacency list: O(degree) checks per vertex = O(E) total
- Total: O(V + E) for adjacency list, O(V²) for adjacency matrix

**Step-by-Step Operations:**
```
Initialize: O(V) - visited array
Enqueue start: O(1)
While loop runs: V times (once per vertex)
  Dequeue: O(1)
  Check neighbors: O(V) with matrix, O(degree) with list
  Enqueue unvisited: O(1) per neighbor
```

#### Space Complexity: **O(V)** - Linear space

| Component | Memory | Explanation |
|-----------|--------|-------------|
| Visited array | V × 1 byte | Boolean array |
| Queue | V × 4 bytes | Maximum V vertices in queue |
| Graph (input) | V² × 4 bytes | Adjacency matrix (not auxiliary) |
| Local variables | ~20 bytes | Counters and pointers |
| **Auxiliary Space** | **O(V)** | Queue + visited array |

**Space Analysis:**
- Visited array: O(V) - tracks visited vertices
- Queue: O(V) worst case - all vertices at same level
- Recursion: None (iterative approach)
- Total auxiliary space: O(V)

**Queue Size Analysis:**
```
Best case: O(1) - linear graph (chain)
Average case: O(V) - balanced tree
Worst case: O(V) - star graph (one center, all connected)
```

**Key Properties:**
- ✅ Complete: Finds all reachable vertices
- ✅ Optimal: Finds shortest path in unweighted graphs
- ✅ Level-order: Visits vertices by distance from source
- ✅ Non-recursive: Uses queue, no stack overflow

**Applications:**
- Shortest path in unweighted graphs
- Level-order traversal
- Connected components
- Bipartite graph checking
- Web crawling

---

## Program 2: Depth-First Search (DFS)

### 📝 Problem Statement
Implement Depth-First Search (DFS) algorithm to traverse a graph starting from a given vertex using recursion.

### 💡 Approach
DFS explores a graph by going as deep as possible along each branch before backtracking. It uses recursion (implicit stack).

**Algorithm:**
1. Mark current vertex as visited
2. Process the current vertex
3. Recursively visit all unvisited neighbors
4. Backtrack when no unvisited neighbors remain

**Key Characteristics:**
- Uses recursion (or explicit stack)
- Explores vertices depth-wise
- Useful for cycle detection and topological sorting

### 💻 Code
[📄 dfs.c](./dfs.c)

```c
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
```

### 🖥️ Sample Output

```
DFS Traversal: 0 1 3 4 2
```

**Working Example:**

```
Graph Structure:
    0 --- 1
    |     |\ 
    |     | \
    2 --- 4  3

Adjacency Matrix:
    0 1 2 3 4
0 [ 0 1 1 0 0 ]
1 [ 1 0 0 1 1 ]
2 [ 1 0 0 0 1 ]
3 [ 0 1 0 0 1 ]
4 [ 0 1 1 1 0 ]

DFS from vertex 0:
Start at 0 → visit 1 → visit 3 → visit 4 → backtrack → visit 2
Traversal: 0 → 1 → 3 → 4 → 2

Recursion Tree:
DFS(0)
  ├─ DFS(1)
  │   ├─ DFS(3)
  │   │   └─ DFS(4)
  │   │       └─ DFS(2) [already visited via 0]
  │   └─ [4 already visited]
  └─ DFS(2)
      └─ [all neighbors visited]
```

### 📊 Complexity Analysis

#### Time Complexity: **O(V + E)** - Linear in graph size

| Operation | Complexity | Explanation |
|-----------|-----------|-------------|
| Visit each vertex | O(V) | Each vertex visited once |
| Explore edges | O(E) | Each edge examined once |
| Recursive calls | O(V) | One call per vertex |
| **Overall (Adjacency Matrix)** | **O(V²)** | Check all matrix entries |
| **Overall (Adjacency List)** | **O(V+E)** | More efficient |

**Detailed Analysis:**
- Each vertex is visited exactly once: O(V)
- Each edge is explored exactly once (in each direction): O(E)
- With adjacency matrix: Must check all V entries for each vertex = O(V²)
- With adjacency list: Only check actual neighbors = O(E)

**Recursion Depth:**
```
Best case: O(log V) - balanced tree
Average case: O(V) - general graph
Worst case: O(V) - linear chain (path graph)
```

#### Space Complexity: **O(V)** - Linear space

| Component | Memory | Explanation |
|-----------|--------|-------------|
| Visited array | V × 1 byte | Boolean array |
| Recursion stack | V × ~50 bytes | Call stack frames |
| Graph (input) | V² × 4 bytes | Adjacency matrix (not auxiliary) |
| Local variables | ~16 bytes | Function parameters |
| **Auxiliary Space** | **O(V)** | Visited + recursion stack |

**Space Analysis:**
- Visited array: O(V)
- Recursion stack: O(V) in worst case (height of recursion tree)
- Each recursive call adds a frame to the call stack
- Maximum depth = longest path without cycles = V

**Call Stack Analysis:**
```
Best case: O(log V) - balanced tree structure
Average case: O(V) - general graph
Worst case: O(V) - linear path graph

Example for linear graph (0→1→2→3→4):
Stack grows: DFS(0) → DFS(1) → DFS(2) → DFS(3) → DFS(4)
Maximum depth: 5 frames = O(V)
```

**Key Properties:**
- ✅ Complete: Finds all reachable vertices
- ❌ Not optimal: Doesn't find shortest path
- ✅ Memory efficient: No queue needed
- ✅ Recursive: Natural implementation
- ⚠️ Stack overflow risk: Deep recursion on large graphs

**Applications:**
- Cycle detection in graphs
- Topological sorting (DAGs)
- Strongly connected components
- Path finding
- Maze solving
- Backtracking problems

---

## 📚 Week 3 Summary

### BFS vs DFS Comparison

| Feature | BFS | DFS |
|---------|-----|-----|
| **Data Structure** | Queue (FIFO) | Stack/Recursion (LIFO) |
| **Time Complexity** | O(V+E) | O(V+E) |
| **Space Complexity** | O(V) | O(V) |
| **Path Type** | Shortest path | Any path |
| **Exploration** | Level by level | Depth first |
| **Implementation** | Iterative | Recursive/Iterative |
| **Memory** | More memory (queue) | Less memory (stack) |
| **Use Case** | Shortest path | Backtracking, cycles |

### Traversal Order Visualization

**Same Graph, Different Orders:**

```
Graph:
    0 --- 1
    |     |\ 
    |     | \
    2 --- 4  3

BFS from 0: 0 → 1 → 2 → 3 → 4 (level order)
DFS from 0: 0 → 1 → 3 → 4 → 2 (depth first)
```

### Complexity Summary

| Algorithm | Time (Adj Matrix) | Time (Adj List) | Space | Best For |
|-----------|------------------|-----------------|-------|----------|
| **BFS** | O(V²) | O(V+E) | O(V) | Shortest path |
| **DFS** | O(V²) | O(V+E) | O(V) | Cycle detection |

### Key Learnings

**1. Graph Representation:**
- Adjacency matrix: O(V²) space, O(1) edge lookup
- Adjacency list: O(V+E) space, O(degree) edge lookup
- Matrix is better for dense graphs, list for sparse graphs

**2. Traversal Strategies:**
- BFS explores breadth-first (level order)
- DFS explores depth-first (branch by branch)
- Both visit all reachable vertices

**3. Queue vs Stack:**
- BFS uses queue → explores nearest vertices first
- DFS uses stack → explores farthest vertices first
- Different orders, same connectivity information

**4. Applications:**
- **BFS:** Shortest path, level order, minimum steps
- **DFS:** Cycle detection, topological sort, connected components

**5. Space-Time Tradeoffs:**
- Both have same time complexity O(V+E)
- BFS may use more space (wider graphs)
- DFS may cause stack overflow (deeper graphs)

### Graph Properties

**Connected Graph:**
- BFS/DFS visits all vertices from any starting point
- Single connected component

**Disconnected Graph:**
- BFS/DFS visits only reachable vertices
- Multiple connected components
- Need to run from multiple starting points

**Directed vs Undirected:**
- Undirected: Edge (u,v) means both u→v and v→u
- Directed: Edge u→v doesn't imply v→u
- Algorithms work for both with appropriate representation

---

## 🎯 Practice Questions

1. **Modify BFS to find shortest path length** between two vertices.
2. **Implement DFS iteratively** using an explicit stack instead of recursion.
3. **Detect cycles in an undirected graph** using DFS.
4. **Find connected components** in a graph using BFS or DFS.
5. **Check if a graph is bipartite** using BFS coloring.
6. **Count number of islands** in a 2D grid (connected 1s).
7. **Implement topological sorting** using DFS.

---

## 🔬 Advanced Topics

### BFS Applications

**1. Shortest Path (Unweighted):**
```c
// Track distances while doing BFS
int distance[MAX];
distance[start] = 0;
// Update distance[neighbor] = distance[curr] + 1
```

**2. Bipartite Graph Check:**
```c
// Color vertices with 2 colors while BFS
// If neighbor has same color → not bipartite
```

### DFS Applications

**1. Cycle Detection:**
```c
// If we visit a vertex that's in current recursion stack
// → cycle exists
```

**2. Topological Sort (DAG):**
```c
// Finish times in DFS give reverse topological order
```

**3. Strongly Connected Components:**
```c
// Use Kosaraju's algorithm with DFS
```

### Time Complexity Deep Dive

**Why O(V+E)?**
- Visit each vertex once: O(V)
- Explore each edge once: O(E)
- Total operations: V + E

**Adjacency Matrix vs List:**
```
Dense graph (E ≈ V²):
  Matrix: O(V²) ✓ Better
  List:   O(V+E) = O(V²)

Sparse graph (E ≈ V):
  Matrix: O(V²)
  List:   O(V+E) = O(V) ✓ Better
```

---

[← Back to Main](../README.md)