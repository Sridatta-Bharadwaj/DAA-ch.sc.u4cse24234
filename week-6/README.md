# Week 6 - Self-Balancing Binary Search Trees

[← Back to Main](../README.md)

---

## 📋 Table of Contents
- [Program 1: AVL Tree](#program-1-avl-tree)
- [Program 2: Red-Black Tree](#program-2-red-black-tree)

---

## Program 1: AVL Tree

### 📝 Problem Statement
Implement an AVL Tree with insert, delete, and search operations. The tree must maintain its balance after every insertion and deletion using rotations.

### 💡 Approach
An AVL Tree is a self-balancing BST where the height difference between the left and right subtrees (balance factor) of any node is at most 1. Whenever an insertion or deletion violates this property, the tree rebalances itself using rotations.

**Algorithm:**
1. Insert/delete using standard BST logic
2. Update height of each node on the way back up
3. Compute balance factor = height(left) - height(right)
4. If balance factor > 1 or < -1, apply appropriate rotation
5. Four rotation cases: LL, RR, LR, RL

**Rotation Cases:**

| Case | Condition | Fix |
|------|-----------|-----|
| LL (Right Rotation) | balance > 1, key < left child | rotateRight |
| RR (Left Rotation) | balance < -1, key > right child | rotateLeft |
| LR (Left-Right) | balance > 1, key > left child | rotateLeft then rotateRight |
| RL (Right-Left) | balance < -1, key < right child | rotateRight then rotateLeft |

### 💻 Code
[📄 avl_tree.c](./avl_tree.c)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
    int height;
} Node;

int height(Node *n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int getBalance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node *newNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node *rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

Node *rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

Node *insert(Node *node, int key) { ... }
Node *deleteNode(Node *root, int key) { ... }
Node *search(Node *root, int key) { ... }
void inorder(Node *root) { ... }
```

### 🖥️ Sample Output

```
1. Insert
2. Delete
3. Search
4. Display (Inorder)
5. Exit
Choice: 1
Enter key: 30
Inserted 30

Choice: 1
Enter key: 20
Inserted 20

Choice: 1
Enter key: 10
Inserted 10

Choice: 4
Inorder: 10 20 30

Choice: 2
Enter key: 20
Deleted 20

Choice: 4
Inorder: 10 30
```

**Working Example (LL Rotation):**

```
Insert 30, 20, 10:

After inserting 30:        After inserting 20:        After inserting 10:
      30                         30                          30  ← balance = 2
                                /                           /
                              20                          20
                                                         /
                                                       10

LL case detected at node 30 → rotateRight(30):

        20
       /  \
     10    30

Tree is balanced again.
```

**Working Example (LR Rotation):**

```
Insert 30, 10, 20:

After inserting 30, 10:    After inserting 20:
      30                         30  ← balance = 2
     /                          /
   10                         10
                                \
                                20

LR case: rotateLeft(10) then rotateRight(30):

Step 1 - rotateLeft(10):       Step 2 - rotateRight(30):
      30                               20
     /                                /  \
   20                               10    30
  /
10

Tree is balanced.
```

### 📊 Complexity Analysis

#### Time Complexity

| Operation | Best | Average | Worst | Explanation |
|-----------|------|---------|-------|-------------|
| **Insert** | O(log n) | O(log n) | O(log n) | Height always O(log n) |
| **Delete** | O(log n) | O(log n) | O(log n) | Height always O(log n) |
| **Search** | O(log n) | O(log n) | O(log n) | Height always O(log n) |
| **Rotation** | O(1) | O(1) | O(1) | Fixed pointer updates |

**Detailed Analysis:**

**Why always O(log n)?**
- AVL property guarantees height ≤ 1.44 × log₂(n)
- This bound holds after every insert/delete due to rebalancing
- Rotations take O(1) — they don't add to the height factor

**Insert:**
- BST insert: O(log n) to find position
- Update heights on backtrack: O(log n)
- At most 2 rotations after insert: O(1)
- Total: O(log n)

**Delete:**
- BST delete: O(log n) to find node
- Update heights and rebalance on backtrack: O(log n)
- May require O(log n) rotations after delete
- Total: O(log n)

#### Space Complexity: **O(n)**

| Component | Memory | Explanation |
|-----------|--------|-------------|
| Tree nodes | 20n bytes | key + left + right + height |
| Recursion stack | O(log n) | Height of tree |
| **Auxiliary Space** | **O(log n)** | Recursion only |
| **Total Space** | **O(n)** | All nodes |

**Key Properties:**
- ✅ Strictly balanced: Height difference ≤ 1 at all nodes
- ✅ Guaranteed O(log n): All operations always logarithmic
- ✅ Better search performance than Red-Black Tree (shorter height)
- ❌ More rotations on insert/delete than Red-Black Tree
- ❌ Extra memory: Stores height in every node

---

## Program 2: Red-Black Tree

### 📝 Problem Statement
Implement a Red-Black Tree with insert, delete, and search operations. The tree must maintain its Red-Black properties after every operation using recoloring and rotations.

### 💡 Approach
A Red-Black Tree is a self-balancing BST where every node is colored RED or BLACK. Five invariants are maintained at all times to ensure the tree stays approximately balanced.

**Red-Black Properties:**
1. Every node is RED or BLACK
2. Root is always BLACK
3. Every leaf (NIL) is BLACK
4. If a node is RED, both children are BLACK (no two consecutive REDs)
5. All paths from any node to its descendant NIL nodes have the same number of BLACK nodes

**Algorithm:**
1. Insert as RED node using standard BST logic
2. Fix violations using `insertFix` — recoloring and rotations
3. Delete using standard BST logic with transplant helper
4. Fix violations using `deleteFix` — recoloring and rotations
5. A sentinel NIL node (always BLACK) is used instead of NULL for cleaner code

### 💻 Code
[📄 red_black_trees.c](./red_black_trees.c)

```c
#include <stdio.h>
#include <stdlib.h>

#define RED   0
#define BLACK 1

typedef struct Node {
    int key, color;
    struct Node *left, *right, *parent;
} Node;

Node *NIL;

void initNIL() {
    NIL = (Node *)malloc(sizeof(Node));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NULL;
}

Node *newNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = NIL;
    return node;
}

void rotateLeft(Node **root, Node *x) { ... }
void rotateRight(Node **root, Node *x) { ... }
void insertFix(Node **root, Node *z) { ... }
void insert(Node **root, int key) { ... }
void deleteFix(Node **root, Node *x) { ... }
void deleteNode(Node **root, int key) { ... }
Node *search(Node *root, int key) { ... }
void inorder(Node *root) { ... }
```

### 🖥️ Sample Output

```
1. Insert
2. Delete
3. Search
4. Display (Inorder)
5. Exit
Choice: 1
Enter key: 10
Inserted 10

Choice: 1
Enter key: 20
Inserted 20

Choice: 1
Enter key: 30
Inserted 30

Choice: 4
Inorder: 10(B) 20(B) 30(R)

Choice: 3
Enter key: 20
Found 20

Choice: 2
Enter key: 10
Choice: 4
Inorder: 20(B) 30(R)
```

**Working Example:**

```
Insert 10, 20, 30:

After insert 10:           After insert 20:
      10(B)                      10(B)
                                    \
                                   20(R)

After insert 30 → violation (two consecutive REDs: 20R → 30R):
      10(B)
         \
         20(R)
            \
            30(R)  ← violation

Uncle of 30 is NIL (BLACK) → RR case → rotateLeft(10):

        20(B)
       /     \
    10(R)   30(R)

Red-Black properties restored.
```

**Insert Fix Cases:**

| Case | Uncle Color | Action |
|------|------------|--------|
| Case 1 | RED | Recolor parent, uncle → BLACK; grandparent → RED |
| Case 2 | BLACK (triangle) | Rotate parent toward grandparent, fall to Case 3 |
| Case 3 | BLACK (line) | Rotate grandparent, recolor |

### 📊 Complexity Analysis

#### Time Complexity

| Operation | Best | Average | Worst | Explanation |
|-----------|------|---------|-------|-------------|
| **Insert** | O(log n) | O(log n) | O(log n) | Height O(log n) guaranteed |
| **Delete** | O(log n) | O(log n) | O(log n) | Height O(log n) guaranteed |
| **Search** | O(log n) | O(log n) | O(log n) | Height O(log n) guaranteed |
| **insertFix** | O(log n) | O(log n) | O(log n) | At most O(log n) recolorings |
| **deleteFix** | O(log n) | O(log n) | O(log n) | At most O(log n) recolorings |

**Detailed Analysis:**

**Why always O(log n)?**
- RB properties guarantee: height ≤ 2 × log₂(n+1)
- This is a looser bound than AVL (1.44 × log n), meaning RB trees can be taller
- But still O(log n) — just with a larger constant

**Insert:**
- BST insert to find position: O(log n)
- insertFix — recoloring propagates up: O(log n)
- At most 2 rotations total per insert: O(1)
- Total: O(log n)

**Delete:**
- BST delete: O(log n)
- deleteFix — at most 3 rotations + O(log n) recoloring
- Total: O(log n)

**AVL vs Red-Black — rotation count:**
```
Insert: AVL ≤ 2 rotations, RBT ≤ 2 rotations
Delete: AVL = O(log n) rotations, RBT ≤ 3 rotations
```
→ Red-Black Trees have faster deletes in practice because fewer rotations are needed.

#### Space Complexity: **O(n)**

| Component | Memory | Explanation |
|-----------|--------|-------------|
| Tree nodes | 24n bytes | key + color + left + right + parent |
| NIL sentinel | 24 bytes | Single shared sentinel node |
| Recursion stack | O(log n) | Height of tree |
| **Auxiliary Space** | **O(log n)** | Recursion only |
| **Total Space** | **O(n)** | All nodes |

**Note:** Each RB node stores an extra `parent` pointer and `color` field compared to a basic BST, making it slightly heavier per node than an AVL node.

**Key Properties:**
- ✅ Approximately balanced: Height ≤ 2 log₂(n+1)
- ✅ Guaranteed O(log n): All operations always logarithmic
- ✅ Fewer rotations on delete than AVL
- ✅ Used in real-world implementations (Linux kernel, Java TreeMap, C++ std::map)
- ❌ More complex to implement than AVL
- ❌ Slightly taller than AVL trees (worse search constants)

---

## 📚 Week 6 Summary

### AVL Tree vs Red-Black Tree

| Feature | AVL Tree | Red-Black Tree |
|---------|----------|----------------|
| **Balance Condition** | Height diff ≤ 1 | Height ≤ 2 log(n+1) |
| **Height Bound** | 1.44 × log n | 2 × log(n+1) |
| **Search Speed** | Faster (shorter tree) | Slightly slower |
| **Insert Rotations** | ≤ 2 | ≤ 2 |
| **Delete Rotations** | O(log n) | ≤ 3 |
| **Extra Storage** | height per node | color + parent per node |
| **Complexity (all ops)** | O(log n) | O(log n) |
| **Best For** | Read-heavy workloads | Write-heavy workloads |

### Complexity Summary

| Operation | BST (avg) | BST (worst) | AVL Tree | Red-Black Tree |
|-----------|-----------|-------------|----------|----------------|
| Insert | O(log n) | O(n) | O(log n) | O(log n) |
| Delete | O(log n) | O(n) | O(log n) | O(log n) |
| Search | O(log n) | O(n) | O(log n) | O(log n) |
| Space | O(n) | O(n) | O(n) | O(n) |

### Key Learnings

**1. Why Self-Balancing Trees?**
- A plain BST degenerates to O(n) for sorted input
- Self-balancing trees maintain O(log n) regardless of input order
- Both AVL and Red-Black trees solve this — with different trade-offs

**2. Rotations:**
- Rotations are O(1) pointer operations
- They preserve BST ordering while changing tree shape
- Left rotation and right rotation are mirror images of each other

**3. AVL is Stricter:**
- AVL enforces tighter balance (|balance factor| ≤ 1)
- Results in shorter trees → faster search
- But requires more rotations on insert/delete to maintain balance

**4. Red-Black is More Relaxed:**
- Looser balance allows slightly taller trees
- Fewer rotations on delete → faster writes
- Preferred in standard library implementations (std::map, TreeMap, Linux scheduler)

**5. The NIL Sentinel (Red-Black):**
- A single shared BLACK NIL node replaces all NULL leaves
- Simplifies boundary condition checks in rotations and fix-up routines
- Avoids special-casing NULL in every comparison

### When to Use Which

**Use AVL Tree when:**
- Lookups are far more frequent than inserts/deletes
- Predictable, tight height bound is required
- Database indexing scenarios

**Use Red-Black Tree when:**
- Frequent insertions and deletions
- Need a general-purpose balanced BST
- Implementing standard library containers (maps, sets)

---

## 🎯 Practice Questions

1. Trace the rotations needed when inserting `[5, 10, 15, 20, 25]` into an AVL tree one by one.
2. What is the minimum and maximum number of nodes in an AVL tree of height h?
3. Why does a Red-Black Tree allow height up to 2 log(n+1)? Prove this from the RB properties.
4. In Red-Black Tree deletion, why do we only need ≤ 3 rotations regardless of tree size?
5. Implement an inorder traversal that prints both key and height for AVL, and key and color for Red-Black.
6. Compare the number of rotations performed when inserting `[1, 2, 3, 4, 5, 6, 7]` into both AVL and Red-Black trees.

---

[← Back to Main](../README.md)