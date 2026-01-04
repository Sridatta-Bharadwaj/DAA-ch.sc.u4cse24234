# Week 5 - Divide and Conquer & Binary Search Trees

[← Back to Main](../README.md)

---

## 📋 Table of Contents
- [Program 1: Merge Sort](#program-1-merge-sort)
- [Program 2: Quick Sort](#program-2-quick-sort)
- [Program 3: Binary Search Tree (BST)](#program-3-binary-search-tree-bst)

---

## Program 1: Merge Sort

### 📝 Problem Statement
Implement Merge Sort algorithm using the divide and conquer approach to sort an array of integers in ascending order.

### 💡 Approach
Merge Sort divides the array into two halves, recursively sorts them, and then merges the sorted halves.

**Algorithm:**
1. **Divide:** Split array into two halves at midpoint
2. **Conquer:** Recursively sort both halves
3. **Combine:** Merge the two sorted halves into one sorted array

**Key Characteristics:**
- Stable sorting algorithm
- Guaranteed O(n log n) performance
- Requires extra space for merging

### 💻 Code
[📄 mergesort.c](./mergesort.c)

```c
#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    print_array(arr, n);
    
    merge_sort(arr, 0, n - 1);
    
    printf("Sorted array: ");
    print_array(arr, n);
    
    return 0;
}
```

### 🖥️ Sample Output

```
Original array: 64 34 25 12 22 11 90 
Sorted array: 11 12 22 25 34 64 90
```

**Working Example:**

```
Initial Array: [64, 34, 25, 12, 22, 11, 90]

Divide Phase:
[64, 34, 25, 12, 22, 11, 90]
    ↓
[64, 34, 25, 12] | [22, 11, 90]
    ↓                   ↓
[64, 34] | [25, 12]  [22, 11] | [90]
   ↓         ↓          ↓         ↓
[64]|[34] [25]|[12]  [22]|[11]  [90]

Conquer Phase (Merge):
[34, 64] | [12, 25]  [11, 22] | [90]
    ↓                   ↓
[12, 25, 34, 64]  |  [11, 22, 90]
    ↓
[11, 12, 22, 25, 34, 64, 90]

Recursion Tree:
                    [64,34,25,12,22,11,90]
                   /                      \
        [64,34,25,12]                  [22,11,90]
        /           \                  /         \
   [64,34]       [25,12]          [22,11]      [90]
    /    \        /    \           /    \        |
  [64]  [34]   [25]  [12]       [22]  [11]    [90]
```

### 📊 Complexity Analysis

#### Time Complexity: **O(n log n)** - Guaranteed

| Case | Complexity | Explanation |
|------|-----------|-------------|
| **Best Case** | **O(n log n)** | Even sorted array needs full split |
| **Average Case** | **O(n log n)** | Standard divide and conquer |
| **Worst Case** | **O(n log n)** | Same as best case |

**Detailed Analysis:**

**Divide Phase:**
- Split array into halves: O(1) per level
- Tree height = log₂(n)
- Total divisions: O(log n)

**Merge Phase:**
- Merge two halves: O(n) comparisons per level
- Each element compared once per level
- log n levels × n comparisons = O(n log n)

**Recurrence Relation:**
```
T(n) = 2T(n/2) + O(n)
     = 2[2T(n/4) + O(n/2)] + O(n)
     = 4T(n/4) + 2O(n/2) + O(n)
     = ... (continue expansion)
     = nT(1) + O(n) × log n
     = O(n log n)
```

**Master Theorem Application:**
- T(n) = aT(n/b) + f(n)
- Here: a=2, b=2, f(n)=O(n)
- log_b(a) = log₂(2) = 1
- f(n) = Θ(n^1) = Θ(n^log_b(a))
- Case 2: T(n) = Θ(n log n)

#### Space Complexity: **O(n)** - Linear Space

| Component | Memory | Explanation |
|-----------|--------|-------------|
| Original array | 4n bytes | Input array |
| Temporary arrays (L, R) | 4n bytes | For merging |
| Recursion stack | O(log n) | Call stack depth |
| Local variables | ~20 bytes | Indices and counters |
| **Auxiliary Space** | **O(n)** | Temporary arrays dominate |

**Space Analysis:**

**Temporary Arrays:**
- Each merge creates temp arrays for subarrays
- Maximum space at any time: O(n)
- Total auxiliary space: O(n)

**Recursion Stack:**
- Maximum depth = log n
- Each frame: O(1) space
- Stack space: O(log n)

**Total: O(n) + O(log n) = O(n)**

**Memory Usage Per Level:**
```
Level 0: n elements (all)
Level 1: n elements (2 arrays of n/2)
Level 2: n elements (4 arrays of n/4)
...
Maximum at any instant: O(n)
```

**Key Properties:**
- ✅ Stable: Maintains relative order of equal elements
- ✅ Consistent: O(n log n) in all cases
- ❌ Not in-place: Requires O(n) extra space
- ✅ Predictable: No worst-case degradation
- ✅ Parallelizable: Can sort subarrays independently

**Advantages:**
- Guaranteed O(n log n) time complexity
- Stable sorting algorithm
- Works well for linked lists (O(1) merge)
- Good for external sorting (large datasets)

**Disadvantages:**
- Requires O(n) extra space
- Not in-place
- Slower than Quick Sort for small arrays

---

## Program 2: Quick Sort

### 📝 Problem Statement
Implement Quick Sort algorithm using divide and conquer with partitioning to sort an array in ascending order.

### 💡 Approach
Quick Sort selects a pivot element and partitions the array so elements smaller than pivot are on the left and larger elements on the right.

**Algorithm:**
1. **Choose pivot:** Select last element as pivot
2. **Partition:** Rearrange array so:
   - Elements < pivot are on left
   - Elements > pivot are on right
   - Pivot is in correct position
3. **Recursively sort:** Apply to left and right subarrays

**Key Characteristics:**
- In-place sorting (O(log n) space)
- Average case O(n log n)
- Unstable algorithm

### 💻 Code
[📄 quicksort.c](./quicksort.c)

```c
#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    print_array(arr, n);
    
    quick_sort(arr, 0, n - 1);
    
    printf("Sorted array: ");
    print_array(arr, n);
    
    return 0;
}
```

### 🖥️ Sample Output

```
Original array: 64 34 25 12 22 11 90 
Sorted array: 11 12 22 25 34 64 90
```

**Working Example:**

```
Initial Array: [64, 34, 25, 12, 22, 11, 90]
Pivot = 90 (last element)

Partition 1: pivot = 90
[64, 34, 25, 12, 22, 11] | 90
All elements < 90, so pivot moves to end
Result: [64, 34, 25, 12, 22, 11, 90]

Partition 2: pivot = 11 (on left subarray)
[11] | [64, 34, 25, 12, 22]
11 is smallest, stays at start

Partition 3: pivot = 22 (on right of 11)
[12] | 22 | [64, 34, 25]

Continue partitioning...
Final: [11, 12, 22, 25, 34, 64, 90]

Detailed Partition Example:
Array: [64, 34, 25, 12, 22, 11, 90], pivot = 90, i = -1

j=0: arr[0]=64 ≤ 90 → i=0, swap arr[0] with arr[0]
j=1: arr[1]=34 ≤ 90 → i=1, swap arr[1] with arr[1]
j=2: arr[2]=25 ≤ 90 → i=2, swap arr[2] with arr[2]
j=3: arr[3]=12 ≤ 90 → i=3, swap arr[3] with arr[3]
j=4: arr[4]=22 ≤ 90 → i=4, swap arr[4] with arr[4]
j=5: arr[5]=11 ≤ 90 → i=5, swap arr[5] with arr[5]

Final swap: arr[i+1]=arr[6] with arr[7]=90
Pivot at index 6: [64, 34, 25, 12, 22, 11, 90]
```

### 📊 Complexity Analysis

#### Time Complexity: **O(n log n)** average, **O(n²)** worst

| Case | Complexity | Condition | Explanation |
|------|-----------|-----------|-------------|
| **Best Case** | **O(n log n)** | Balanced partitions | Pivot divides evenly |
| **Average Case** | **O(n log n)** | Random input | Expected balanced splits |
| **Worst Case** | **O(n²)** | Already sorted | Unbalanced partitions |

**Detailed Analysis:**

**Best Case (Balanced Partitions):**
- Pivot divides array into equal halves
- Recurrence: T(n) = 2T(n/2) + O(n)
- Solution: T(n) = O(n log n)
- Tree height: log n
- Work per level: O(n)

**Average Case:**
- Most partitions are reasonably balanced
- Even 9:1 split gives O(n log n)
- Statistically, most random arrays balanced
- Expected: O(n log n)

**Worst Case (Unbalanced Partitions):**
- Already sorted or reverse sorted
- Pivot always smallest/largest
- Recurrence: T(n) = T(n-1) + O(n)
- Solution: T(n) = O(n²)
- Creates linear recursion tree

**Partition Complexity:**
```
Single partition: O(n) comparisons
Best case: log n levels → n log n
Worst case: n levels → n²
Average case: log n levels → n log n
```

**Recurrence Relations:**
```
Best: T(n) = 2T(n/2) + Θ(n) = Θ(n log n)
Worst: T(n) = T(n-1) + Θ(n) = Θ(n²)
Average: T(n) = T(n/10) + T(9n/10) + Θ(n) = Θ(n log n)
```

#### Space Complexity: **O(log n)** average, **O(n)** worst

| Component | Memory | Explanation |
|-----------|--------|-------------|
| Original array | 4n bytes | Input (in-place) |
| Recursion stack (avg) | O(log n) | Balanced recursion |
| Recursion stack (worst) | O(n) | Linear recursion |
| Local variables | ~16 bytes | Indices and pivot |
| **Auxiliary Space (avg)** | **O(log n)** | Stack frames |
| **Auxiliary Space (worst)** | **O(n)** | Deep recursion |

**Space Analysis:**

**Best/Average Case:**
- Balanced partitions
- Recursion depth: O(log n)
- Each call: O(1) space
- Total: O(log n) stack space

**Worst Case:**
- Unbalanced partitions
- Recursion depth: O(n)
- Linear call stack
- Risk of stack overflow for large n

**Stack Frame Usage:**
```
Best case depth: log₂ n
Worst case depth: n
Each frame: ~40 bytes (variables, return address)
```

**Key Properties:**
- ❌ Unstable: May change relative order of equal elements
- ✅ In-place: O(log n) space (excluding worst case)
- ✅ Cache-friendly: Good locality of reference
- ❌ Worst case O(n²): Requires randomization/median pivot
- ✅ Practical: Usually faster than Merge Sort

**Advantages:**
- In-place sorting (low memory)
- Average O(n log n) performance
- Cache-friendly (good locality)
- Often fastest in practice

**Disadvantages:**
- Worst case O(n²) time
- Unstable algorithm
- Not suitable for linked lists
- Recursion depth issues on sorted data

**Optimization Strategies:**
1. **Random pivot:** Choose random element as pivot
2. **Median-of-three:** Use median of first, middle, last
3. **Tail recursion:** Eliminate one recursive call
4. **Hybrid approach:** Switch to Insertion Sort for small subarrays

---

## Program 3: Binary Search Tree (BST)

### 📝 Problem Statement
Implement a Binary Search Tree with operations: insert, search, delete, and three types of traversals (inorder, preorder, postorder).

### 💡 Approach
A Binary Search Tree is a binary tree where for each node:
- Left subtree contains only nodes with values less than the node
- Right subtree contains only nodes with values greater than the node
- Both subtrees are also BSTs

**BST Property:**
- For node with value x:
  - All left descendants < x
  - All right descendants > x

### 💻 Code
[📄 bst.c](./bst.c)

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    
    return root;
}

bool search(Node* root, int data) {
    if (root == NULL) {
        return false;
    }
    
    if (root->data == data) {
        return true;
    }
    
    if (data < root->data) {
        return search(root->left, data);
    }
    return search(root->right, data);
}

Node* find_min(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* delete_node(Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {
        // Node with one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children
        Node* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    
    int elements[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(elements) / sizeof(elements[0]);
    
    for (int i = 0; i < n; i++) {
        root = insert(root, elements[i]);
    }
    
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
    
    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");
    
    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");
    
    printf("\nSearch 40: %s\n", search(root, 40) ? "Found" : "Not found");
    printf("Search 100: %s\n", search(root, 100) ? "Found" : "Not found");
    
    root = delete_node(root, 30);
    printf("\nAfter deleting 30: ");
    inorder(root);
    printf("\n");
    
    free_tree(root);
    
    return 0;
}
```

### 🖥️ Sample Output

```
Inorder traversal: 20 30 40 50 60 70 80 
Preorder traversal: 50 30 20 40 70 60 80 
Postorder traversal: 20 40 30 60 80 70 50 

Search 40: Found
Search 100: Not found

After deleting 30: 20 40 50 60 70 80
```

**Working Example:**

```
Building BST with: [50, 30, 70, 20, 40, 60, 80]

Step 1: Insert 50
       50

Step 2: Insert 30 (30 < 50, go left)
       50
      /
     30

Step 3: Insert 70 (70 > 50, go right)
       50
      /  \
     30   70

Step 4: Insert 20 (20 < 50, 20 < 30, go left of 30)
       50
      /  \
     30   70
    /
   20

Step 5: Insert 40 (40 < 50, 40 > 30, go right of 30)
       50
      /  \
     30   70
    /  \
   20   40

Step 6: Insert 60 (60 > 50, 60 < 70, go left of 70)
       50
      /  \
     30   70
    /  \  / \
   20 40 60 80

Final BST:
       50
      /  \
     30   70
    /  \  / \
   20 40 60 80

Traversals:
- Inorder (Left-Root-Right): 20 30 40 50 60 70 80 (Sorted!)
- Preorder (Root-Left-Right): 50 30 20 40 70 60 80
- Postorder (Left-Right-Root): 20 40 30 60 80 70 50

Delete 30 (node with two children):
1. Find inorder successor (smallest in right subtree) = 40
2. Replace 30 with 40
3. Delete original 40 node

Result:
       50
      /  \
     40   70
    /    / \
   20   60 80
```

### 📊 Complexity Analysis

#### Time Complexity

| Operation | Best | Average | Worst | Explanation |
|-----------|------|---------|-------|-------------|
| **Insert** | O(log n) | O(log n) | O(n) | Height of tree |
| **Search** | O(log n) | O(log n) | O(n) | Path from root to node |
| **Delete** | O(log n) | O(log n) | O(n) | Search + deletion |
| **Traversal** | O(n) | O(n) | O(n) | Visit all nodes |

**Detailed Analysis:**

**Insert Operation:**
- Best case (balanced): O(log n)
  - Tree height = log n
  - Follow one path down
- Worst case (skewed): O(n)
  - Tree becomes linked list
  - Height = n

**Search Operation:**
- Compare with root
- Recursively search left or right
- Best: O(log n) - balanced tree
- Worst: O(n) - linear tree

**Delete Operation:**
Three cases:
1. Leaf node: O(h) to find, O(1) to delete
2. One child: O(h) to find, O(1) to delete
3. Two children: O(h) to find + O(h) to find successor

**Traversal Operations:**
- Visit each node exactly once
- Always O(n) regardless of tree shape

**Tree Heights:**
```
Balanced BST:
Height = log n
Operations = O(log n)

Skewed BST (worst):
Height = n
Operations = O(n)

Example with n=7:
Balanced: height = 3
Skewed: height = 7
```

#### Space Complexity

| Operation | Space | Explanation |
|-----------|-------|-------------|
| **Tree Storage** | O(n) | One node per element |
| **Insert** | O(h) | Recursion stack |
| **Search** | O(h) | Recursion stack |
| **Delete** | O(h) | Recursion stack |
| **Traversal** | O(h) | Recursion stack |

**Space Analysis:**

**Tree Storage:**
- Each node: 16 bytes (data + 2 pointers)
- n nodes: 16n bytes = O(n)

**Recursion Space:**
- Best case (balanced): O(log n)
- Worst case (skewed): O(n)
- Each recursive call adds stack frame

**Memory Breakdown:**
```
Per Node:
- int data: 4 bytes
- Node* left: 8 bytes
- Node* right: 8 bytes
Total: 20 bytes per node

For n nodes: 20n bytes
```

**Key Properties:**
- ✅ Dynamic: Easy insertion and deletion
- ✅ Ordered: Inorder traversal gives sorted sequence
- ✅ Search efficient: O(log n) average
- ❌ Can degrade: Becomes O(n) if unbalanced
- ⚠️ Balance matters: Need self-balancing for guaranteed performance

**BST vs Array:**

| Operation | BST (balanced) | Sorted Array |
|-----------|----------------|--------------|
| Search | O(log n) | O(log n) |
| Insert | O(log n) | O(n) |
| Delete | O(log n) | O(n) |
| Min/Max | O(log n) | O(1) |
| Space | O(n) | O(n) |

**Traversal Explanations:**

**Inorder (Left-Root-Right):**
- Visits nodes in ascending order
- Used for getting sorted sequence
- Result: 20 30 40 50 60 70 80

**Preorder (Root-Left-Right):**
- Visits root before subtrees
- Used for copying tree structure
- Result: 50 30 20 40 70 60 80

**Postorder (Left-Right-Root):**
- Visits root after subtrees
- Used for deleting tree
- Result: 20 40 30 60 80 70 50

**Advantages:**
- Efficient search, insert, delete (O(log n) average)
- Maintains sorted order
- Dynamic size
- No waste of space

**Disadvantages:**
- Can become unbalanced (O(n) worst case)
- More complex than arrays
- Extra space for pointers
- Not cache-friendly

**When to Use BST:**
- Need frequent insertions/deletions
- Need to maintain sorted order
- Search performance important
- Unknown size of dataset

**Self-Balancing Trees:**
For guaranteed O(log n) performance:
- AVL Trees
- Red-Black Trees
- B-Trees
These maintain balance automatically

---

## 📚 Week 5 Summary

### Algorithm Comparison

| Algorithm | Type | Best | Average | Worst | Space | Stable |
|-----------|------|------|---------|-------|-------|--------|
| **Merge Sort** | Divide & Conquer | O(n log n) | O(n log n) | O(n log n) | O(n) | ✅ Yes |
| **Quick Sort** | Divide & Conquer | O(n log n) | O(n log n) | O(n²) | O(log n) | ❌ No |

### Data Structure Comparison

| Structure | Search | Insert | Delete | Space | Ordered |
|-----------|--------|--------|--------|-------|---------|
| **BST** | O(log n)* | O(log n)* | O(log n)* | O(n) | ✅ Yes |
| **Array (sorted)** | O(log n) | O(n) | O(n) | O(n) | ✅ Yes |
| **Linked List** | O(n) | O(1) | O(1)** | O(n) | ❌ No |

*Average case; worst case O(n) for unbalanced BST  
**After finding node

### Key Learnings

**1. Divide and Conquer Paradigm:**
- Break problem into smaller subproblems
- Solve subproblems recursively
- Combine solutions
- Examples: Merge Sort, Quick Sort

**2. Merge Sort vs Quick Sort:**

| Feature | Merge Sort | Quick Sort |
|---------|-----------|------------|
| Stability | ✅ Stable | ❌ Unstable |
| Space | O(n) | O(log n) |
| Worst Case | O(n log n) | O(n²) |
| In-place | ❌ No | ✅ Yes |
| Practical Speed | Slower | Faster |
| Best For | Linked lists, stability | Arrays, general use |

**3. BST Properties:**
- Inorder traversal → sorted sequence
- Average O(log n) operations
- Can degrade to O(n) if unbalanced
- Foundation for advanced trees (AVL, Red-Black)

**4. Recursion Patterns:**
- All three algorithms use recursion
- Merge Sort: Always splits evenly
- Quick Sort: Split depends on pivot
- BST: Recursive by structure

**5. Space-Time Tradeoffs:**
- Merge Sort: Extra space for guaranteed performance
- Quick Sort: In-place