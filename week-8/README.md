# Week 8 - Greedy Algorithms: Job Sequencing & Huffman Coding

[← Back to Main](../README.md)

---

## 📋 Table of Contents
- [Program 1: Job Sequencing with Deadlines](#program-1-job-sequencing-with-deadlines)
- [Program 2: Huffman Coding](#program-2-huffman-coding)

---

## Program 1: Job Sequencing with Deadlines

### 📝 Problem Statement
Given 14 jobs J1 to J14 with associated profits and deadlines, schedule the maximum profit subset of jobs such that each job is completed within its deadline. Each job takes exactly one unit of time.

**Input Data:**

| Job | Profit | Deadline |
|-----|--------|----------|
| J1  | 36     | 5        |
| J2  | 21     | 8        |
| J3  | 28     | 3        |
| J4  | 19     | 4        |
| J5  | 21     | 4        |
| J6  | 13     | 9        |
| J7  | 28     | 12       |
| J8  | 25     | 14       |
| J9  | 18     | 2        |
| J10 | 20     | 7        |
| J11 | 27     | 5        |
| J12 | 22     | 1        |
| J13 | 14     | 6        |
| J14 | 26     | 3        |

### 💡 Approach
Job Sequencing uses a greedy strategy — always pick the highest profit job first and assign it to the latest available slot before its deadline.

**Algorithm:**
1. Sort all jobs in descending order of profit
2. For each job (in sorted order):
   - Find the latest free slot ≤ deadline
   - If a free slot exists, assign the job to it
   - If no free slot exists, skip the job
3. Output the scheduled jobs and total profit

**Key Insight:**
- Assigning to the latest available slot keeps earlier slots free for future jobs with tighter deadlines
- This greedy choice is provably optimal for maximising profit

### 💻 Code
[📄 job_sequencing.c](./job_sequencing.c)

```c
typedef struct {
    int id, profit, deadline;
} Job;

void jobSequencing(Job jobs[], int n) {
    sortByProfit(jobs, n);  // descending order

    int slot[MAX];
    memset(slot, -1, sizeof(slot));
    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }
}
```

### 🖥️ Sample Output

```
Job Sequencing with Deadlines
==============================
Job     Profit  Deadline
J1      36      5
J2      21      8
...
J14     26      3

Selected Jobs (in slot order):
Slot    Job ID  Profit
1       J12     22
2       J14     26
3       J3      28
4       J11     27
5       J1      36
6       J13     14
7       J10     20
8       J2      21
9       J6      13
12      J7      28
14      J8      25

Total Profit: 260
Number of Jobs Scheduled: 11
```

**Working Example — Step by Step:**

Jobs sorted by profit (descending):

| Order | Job | Profit | Deadline |
|-------|-----|--------|----------|
| 1     | J1  | 36     | 5        |
| 2     | J3  | 28     | 3        |
| 3     | J7  | 28     | 12       |
| 4     | J11 | 27     | 5        |
| 5     | J14 | 26     | 3        |
| 6     | J8  | 25     | 14       |
| 7     | J12 | 22     | 1        |
| 8     | J2  | 21     | 8        |
| 9     | J5  | 21     | 4        |
| 10    | J10 | 20     | 7        |
| 11    | J9  | 18     | 2        |
| 12    | J4  | 19     | 4        |
| 13    | J13 | 14     | 6        |
| 14    | J6  | 13     | 9        |

```
Greedy assignment:
J1  (profit=36, deadline=5) → slot 5 ✓
J3  (profit=28, deadline=3) → slot 3 ✓
J7  (profit=28, deadline=12)→ slot 12 ✓
J11 (profit=27, deadline=5) → slot 4 ✓
J14 (profit=26, deadline=3) → slot 2 ✓
J8  (profit=25, deadline=14)→ slot 14 ✓
J12 (profit=22, deadline=1) → slot 1 ✓
J2  (profit=21, deadline=8) → slot 8 ✓
J5  (profit=21, deadline=4) → slot 3? taken, 2? taken, 1? taken → skipped ✗
J10 (profit=20, deadline=7) → slot 7 ✓
J9  (profit=18, deadline=2) → slot 2? taken, 1? taken → skipped ✗
J4  (profit=19, deadline=4) → all slots 1-4 taken → skipped ✗
J13 (profit=14, deadline=6) → slot 6 ✓
J6  (profit=13, deadline=9) → slot 9 ✓

Final slots: [J12, J14, J3, J11, J1, J13, J10, J2, J6, _, _, J7, _, J8]
Total Profit: 260  |  Jobs scheduled: 11/14
```

### 📊 Complexity Analysis

#### Time Complexity

| Step | Complexity | Explanation |
|------|-----------|-------------|
| Sort by profit | O(n²) | Bubble sort used |
| Slot assignment | O(n × d) | n jobs, each scans up to d slots |
| **Overall** | **O(n × d)** | d = max deadline |

**With efficient sorting (merge/quick sort):** O(n log n + n×d)

For this problem: n=14, d=14 → very fast in practice.

#### Space Complexity: **O(d)**

| Component | Space | Explanation |
|-----------|-------|-------------|
| Slot array | O(d) | One entry per time slot |
| Result array | O(n) | Scheduled job indices |
| **Auxiliary** | **O(n + d)** | Both arrays |

**Key Properties:**
- ✅ Greedy: Provably optimal for maximising profit
- ✅ Simple: No dynamic programming needed
- ✅ In-place scheduling: Assigns slots directly
- ❌ Bubble sort used here: Can be improved to O(n log n) with better sort

---

## Program 2: Huffman Coding

### 📝 Problem Statement
Build a Huffman encoding tree for the phrase **"AMRITA VISHWA VIDYAPEETHAM CHENNAI CAMPUS"** and generate optimal binary codes for each character to achieve maximum compression.

### 💡 Approach
Huffman Coding is a greedy algorithm that assigns shorter codes to more frequent characters and longer codes to less frequent ones, minimising total encoded length.

**Algorithm:**
1. Count frequency of each character in the input
2. Create a leaf node for each character and insert into a min-heap
3. While heap has more than one node:
   - Extract the two nodes with lowest frequency
   - Create a new internal node with their combined frequency
   - Insert the new node back into the heap
4. The remaining node is the root of the Huffman tree
5. Traverse the tree: go left → append '0', go right → append '1'
6. The path from root to each leaf is that character's code

**Key Insight:**
- More frequent characters get shorter codes (closer to root)
- Less frequent characters get longer codes (deeper in tree)
- No code is a prefix of another (prefix-free property)

### 💻 Code
[📄 huffman.c](./huffman.c)

```c
Node *buildHuffmanTree(char chars[], int freq[], int n) {
    MinHeap h; h.size = 0;
    for (int i = 0; i < n; i++)
        insert(&h, newNode(chars[i], freq[i]));

    while (h.size > 1) {
        Node *left  = extractMin(&h);
        Node *right = extractMin(&h);
        Node *merged = newNode('$', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        insert(&h, merged);
    }
    return extractMin(&h);
}
```

### 🖥️ Sample Output

```
Huffman Coding
==============
Input: AMRITA VISHWA VIDYAPEETHAM CHENNAI CAMPUS

Character Frequencies:
Char    Frequency
SPACE   4
A       7
C       2
D       1
E       3
H       3
I       4
M       3
N       2
P       2
R       1
S       2
T       2
U       1
V       2
W       1
Y       1

Huffman Codes:
Char    Freq    Code        Bits
SPACE   4       001         3
A       7       110         3
C       2       0000        4
D       1       111110      6
E       3       1011        4
H       3       1010        4
I       4       010         3
M       3       1001        4
N       2       11110       5
P       2       0001        4
R       1       111111      6
S       2       1000        4
T       2       0111        4
U       1       11100       5
V       2       0110        4
W       1       111010      6
Y       1       111011      6

Total characters: 41
Unique characters: 17
Bits with Huffman encoding: 160
Bits with fixed 8-bit encoding: 328
Compression ratio: 51.22%
```

**Character Frequency Table:**

| Character | Frequency | Huffman Code | Code Length |
|-----------|-----------|--------------|-------------|
| A         | 7         | 110          | 3           |
| SPACE     | 4         | 001          | 3           |
| I         | 4         | 010          | 3           |
| E         | 3         | 1011         | 4           |
| H         | 3         | 1010         | 4           |
| M         | 3         | 1001         | 4           |
| C         | 2         | 0000         | 4           |
| N         | 2         | 11110        | 5           |
| P         | 2         | 0001         | 4           |
| S         | 2         | 1000         | 4           |
| T         | 2         | 0111         | 4           |
| V         | 2         | 0110         | 4           |
| D         | 1         | 111110       | 6           |
| R         | 1         | 111111       | 6           |
| U         | 1         | 11100        | 5           |
| W         | 1         | 111010       | 6           |
| Y         | 1         | 111011       | 6           |

**Huffman Tree Structure (partial):**

```
                    root(41)
                   /        \
              (18)            (23)
             /    \          /    \
           (8)    A(7)    (11)    (12)
          /   \          /   \   /    \
       (4)    (4)      (5)  (6) A... ...
      / \    / \
  SPACE  I  ...
```

Higher frequency characters (A=7, SPACE=4, I=4) sit closer to the root and get 3-bit codes, while rare characters (D, R, W, Y with freq=1) get 6-bit codes.

### 📊 Complexity Analysis

#### Time Complexity

| Step | Complexity | Explanation |
|------|-----------|-------------|
| Count frequencies | O(n) | Single pass through input |
| Build initial heap | O(k log k) | k unique characters |
| Build Huffman tree | O(k log k) | k-1 merge operations |
| Generate codes | O(k) | One DFS traversal |
| **Overall** | **O(n + k log k)** | n = input length, k = unique chars |

For this problem: n=41, k=17 → extremely fast.

**Heap operations:**
- Each extract-min: O(log k)
- Each insert: O(log k)
- Total merges: k-1 = 16
- Total heap ops: 2(k-1) = O(k log k)

#### Space Complexity: **O(k)**

| Component | Space | Explanation |
|-----------|-------|-------------|
| Frequency array | O(1) | Fixed 256-char array |
| Huffman tree nodes | O(k) | 2k-1 nodes total |
| Min-heap | O(k) | At most k nodes at once |
| Code strings | O(k × L) | L = max code length ≈ log k |
| **Auxiliary** | **O(k log k)** | Dominated by code storage |

**Key Properties:**
- ✅ Optimal: Produces minimum total encoded length (provably)
- ✅ Prefix-free: No code is a prefix of another — unambiguous decoding
- ✅ Lossless: Original data perfectly recoverable
- ❌ Requires frequency table: Must be transmitted with encoded data
- ❌ Not adaptive: Frequencies must be known before encoding

**Compression achieved:**
```
Fixed 8-bit encoding:  41 chars × 8 bits = 328 bits
Huffman encoding:                          160 bits
Space saved:                               168 bits
Compression ratio:                         51.22%
```

---

## 📚 Week 8 Summary

### Job Sequencing vs Huffman — Greedy Comparison

| Feature | Job Sequencing | Huffman Coding |
|---------|---------------|----------------|
| **Greedy Choice** | Highest profit job first | Lowest frequency nodes first |
| **Data Structure** | Slot array | Min-heap + binary tree |
| **Optimality** | Provably optimal | Provably optimal |
| **Time** | O(n × d) | O(n + k log k) |
| **Space** | O(n + d) | O(k log k) |
| **Output** | Job schedule + profit | Binary codes + compressed size |

### Complexity Summary

| Algorithm | Time | Space | Greedy Property |
|-----------|------|-------|-----------------|
| Job Sequencing | O(n × d) | O(n + d) | Max profit job first |
| Huffman Coding | O(n + k log k) | O(k log k) | Min frequency merge first |

### Key Learnings

**1. Greedy Algorithms are Powerful:**
- Both algorithms make locally optimal choices that lead to globally optimal solutions
- This is not always the case — greedy only works when the problem has the greedy-choice property

**2. Job Sequencing — Latest Slot Assignment:**
- Always assign to the latest available slot, not the earliest
- This preserves earlier slots for jobs with tighter deadlines
- Skipping a job entirely is sometimes the right greedy choice

**3. Huffman Coding — Variable Length Codes:**
- More frequent → shorter code → less total bits
- The prefix-free property ensures unambiguous decoding without separators
- A 51.22% compression ratio was achieved on this input

**4. Min-Heap in Huffman:**
- The min-heap efficiently gives the two lowest-frequency nodes in O(log k)
- Without it, finding the minimum would be O(k) per step → O(k²) total

**5. Real-World Usage:**
- Job Sequencing: CPU scheduling, task management systems
- Huffman Coding: Used in ZIP, JPEG, MP3, and HTTP compression (deflate)

---

## 🎯 Practice Questions

1. What happens in Job Sequencing if two jobs have the same profit? How does the algorithm break ties?
2. In the given problem, which 3 jobs were skipped and why?
3. Prove that the greedy choice in Job Sequencing (highest profit first) is optimal.
4. Decode the Huffman-encoded string `110 001 110` using the codes generated above.
5. What would the Huffman codes look like if all characters had equal frequency?
6. Why is Huffman Coding called a prefix-free code? Why does this matter for decoding?
7. Modify Job Sequencing to also output which jobs were skipped and the profit lost.

---

[← Back to Main](../README.md)