# Week 7 - Quick Sort Variants & Quick Select

[← Back to Main](../README.md)

---

## 📋 Table of Contents
- [Program 1: Quick Sort with Three Different Pivots](#program-1-quick-sort-with-three-different-pivots)
- [Program 2: Quick Select](#program-2-quick-select)

---

## Program 1: Quick Sort with Three Different Pivots

### 📝 Problem Statement
Implement Quick Sort using three different pivot selection strategies — last element, first element, and median-of-three — and compare their behaviour on the same input.

### 💡 Approach
Quick Sort performance heavily depends on pivot selection. A bad pivot (always smallest or largest) degrades the algorithm to O(n²). Three common strategies are compared:

**Pivot Strategies:**

| Strategy | Pivot Chosen | Risk |
|----------|-------------|------|
| Last element | `arr[high]` | Worst case on sorted input |
| First element | `arr[low]` | Worst case on sorted input |
| Median-of-three | Median of `arr[low]`, `arr[mid]`, `arr[high]` | Avoids sorted-input worst case |

**Algorithm (common to all three):**
1. Select pivot using the chosen strategy
2. Partition: move elements smaller than pivot to the left, larger to the right
3. Pivot is now in its final sorted position
4. Recursively apply to left and right subarrays

**Median-of-Three Detail:**
- Compare `arr[low]`, `arr[mid]`, `arr[high]`
- Sort these three in place
- Use `arr[mid]` (now the median) as pivot
- Swap it to `arr[high]` and run standard partition

### 💻 Code
[📄 quick_sort_pivots.c](./quick_sort_pivots.c)

```c
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a; *a = *b; *b = temp;
}

int partitionLast(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot) swap(&arr[++i], &arr[j]);
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int partitionFirst(int arr[], int low, int high) {
    swap(&arr[low], &arr[high]);
    return partitionLast(arr, low, high);
}

int partitionMedian(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid])  swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high]) swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);
    swap(&arr[mid], &arr[high]);
    return partitionLast(arr, low, high);
}

void quickSortLast(int arr[], int low, int high)   { ... }
void quickSortFirst(int arr[], int low, int high)  { ... }
void quickSortMedian(int arr[], int low, int high) { ... }
```

### 🖥️ Sample Output

**Input array:** `{64, 25, 12, 22, 11, 90, 45}`

```
Original array:        64 25 12 22 11 90 45
Sorted (Last pivot):   11 12 22 25 45 64 90
Sorted (First pivot):  11 12 22 25 45 64 90
Sorted (Median pivot): 11 12 22 25 45 64 90
```

**Working Example — Last Pivot:**

```
Array: [64, 25, 12, 22, 11, 90, 45]   pivot = 45

Partition:
Elements ≤ 45: 25, 12, 22, 11 → go left
Elements > 45: 64, 90         → go right

After partition: [25, 12, 22, 11, 45, 90, 64]
                               ↑ pivot in final position (index 4)

Recurse left:  [25, 12, 22, 11] → sorts to [11, 12, 22, 25]
Recurse right: [90, 64]         → sorts to [64, 90]

Final: [11, 12, 22, 25, 45, 64, 90]
```

**Working Example — Median-of-Three:**

```
Array: [64, 25, 12, 22, 11, 90, 45]
low=0 (64), mid=3 (22), high=6 (45)

Sort these three: 22, 45, 64
Median = 45 → swap to arr[high]

Array becomes: [64, 25, 12, 22, 11, 90, 45]
                                          ↑ same pivot here, but on
                                            sorted/skewed inputs
                                            median picks a better pivot
```

### 📊 Complexity Analysis

#### Time Complexity

| Pivot Strategy | Best | Average | Worst | Worst Case Trigger |
|---------------|------|---------|-------|--------------------|
| Last element | O(n log n) | O(n log n) | O(n²) | Already sorted array |
| First element | O(n log n) | O(n log n) | O(n²) | Already sorted array |
| Median-of-three | O(n log n) | O(n log n) | O(n²) | Specifically crafted input |

**Detailed Analysis:**

**Best Case (balanced partition):**
- Pivot divides array into equal halves every time
- Recurrence: T(n) = 2T(n/2) + O(n) → O(n log n)

**Worst Case (unbalanced partition):**
- Pivot is always smallest or largest element
- Recurrence: T(n) = T(n-1) + O(n) → O(n²)
- Last/First pivot hits this on sorted input
- Median-of-three avoids this for sorted input but not all adversarial inputs

**Average Case:**
- Random input → partitions are reasonably balanced
- T(n) = O(n log n) for all three strategies

**Comparison of pivot strategies on sorted input [1,2,3,4,5,6,7]:**
```
Last pivot:         7 partitions of size 0 and n-1 → O(n²)
First pivot:        7 partitions of size 0 and n-1 → O(n²)
Median-of-three:    Picks actual median → balanced → O(n log n)
```

#### Space Complexity

| Pivot Strategy | Average | Worst | Explanation |
|---------------|---------|-------|-------------|
| Last element | O(log n) | O(n) | Recursion stack depth |
| First element | O(log n) | O(n) | Recursion stack depth |
| Median-of-three | O(log n) | O(n) | Recursion stack depth |

**Key Properties:**
- ❌ Unstable: Relative order of equal elements not preserved
- ✅ In-place: O(log n) auxiliary space on average
- ✅ Median-of-three: Best practical choice for real-world data
- ❌ All three degrade to O(n²) in adversarial worst case (use randomized pivot to fully avoid)

---

## Program 2: Quick Select

### 📝 Problem Statement
Given an unsorted array of n elements, find the k-th smallest element efficiently without fully sorting the array.

### 💡 Approach
Quick Select is a selection algorithm derived from Quick Sort. Instead of recursing into both subarrays, it recurses only into the subarray that contains the k-th smallest element. This reduces average time from O(n log n) to O(n).

**Algorithm:**
1. Choose pivot (last element) and partition the array
2. Let `pos` = number of elements in the left partition + 1 (pivot's rank)
3. If `pos == k` → pivot is the answer, return it
4. If `k < pos` → recurse into left subarray
5. If `k > pos` → recurse into right subarray with `k = k - pos`

**Key Insight:**
- After partition, pivot is in its correct sorted position
- We only need to recurse into one side — halving the problem each time on average

### 💻 Code
[📄 quick_select.c](./quick_select.c)

```c
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a; *a = *b; *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot) swap(&arr[++i], &arr[j]);
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int quickSelect(int arr[], int low, int high, int k) {
    if (low == high) return arr[low];

    int pi  = partition(arr, low, high);
    int pos = pi - low + 1;

    if (pos == k)       return arr[pi];
    else if (k < pos)   return quickSelect(arr, low, pi - 1, k);
    else                return quickSelect(arr, pi + 1, high, k - pos);
}

int main() {
    int arr[] = {64, 25, 12, 22, 11, 90, 45};
    int n = 7, k;
    printf("Array: "); // print array
    printf("Enter k (1 to %d): ", n);
    scanf("%d", &k);
    printf("The %d-th smallest element is: %d\n", k,
           quickSelect(arr, 0, n - 1, k));
}
```

### 🖥️ Sample Output

**Input array:** `{64, 25, 12, 22, 11, 90, 45}`

```
Array: 64 25 12 22 11 90 45
Enter k (1 to 7): 3
The 3rd smallest element is: 22
```

```
Array: 64 25 12 22 11 90 45
Enter k (1 to 7): 1
The 1st smallest element is: 11
```

```
Array: 64 25 12 22 11 90 45
Enter k (1 to 7): 7
The 7th smallest element is: 90
```

**Working Example (k = 3):**

```
Array: [64, 25, 12, 22, 11, 90, 45]   k = 3

Step 1: partition with pivot = 45
After:  [25, 12, 22, 11, 45, 90, 64]
                         ↑ pivot at index 4, pos = 5
k=3 < pos=5 → recurse LEFT into [25, 12, 22, 11]

Step 2: partition [25, 12, 22, 11] with pivot = 11
After:  [11, 25, 12, 22]
         ↑ pivot at index 0, pos = 1
k=3 > pos=1 → recurse RIGHT into [25, 12, 22] with k = 3-1 = 2

Step 3: partition [25, 12, 22] with pivot = 22
After:  [12, 22, 25]
             ↑ pivot at index 1, pos = 2
k=2 == pos=2 → return arr[pi] = 22 ✓

Sorted array for reference: [11, 12, 22, 25, 45, 64, 90]
3rd smallest = 22 ✓
```

**Quick Select vs Quick Sort — what changes:**

```
Quick Sort:  recurse LEFT  AND  RIGHT  → O(n log n)
Quick Select: recurse LEFT  OR   RIGHT  → O(n) average
                             ↑
                        only the side that contains k
```

### 📊 Complexity Analysis

#### Time Complexity

| Case | Complexity | Condition | Explanation |
|------|-----------|-----------|-------------|
| **Best Case** | **O(n)** | Pivot always median | Halves problem each time |
| **Average Case** | **O(n)** | Random input | Expected linear time |
| **Worst Case** | **O(n²)** | Pivot always min/max | Degrades like Quick Sort |

**Detailed Analysis:**

**Average Case — O(n):**
- Each partition reduces problem size by roughly half on average
- Work per level: n + n/2 + n/4 + ... = 2n = O(n)
- This is the key advantage over sorting

**Recurrence (average):**
```
T(n) = T(n/2) + O(n)
     = O(n) + O(n/2) + O(n/4) + ...
     = O(n × (1 + 1/2 + 1/4 + ...))
     = O(n × 2)
     = O(n)
```

**Worst Case — O(n²):**
- Pivot always smallest or largest
- T(n) = T(n-1) + O(n) → O(n²)
- Same as Quick Sort worst case

**Comparison with alternatives:**

| Method | Time | Notes |
|--------|------|-------|
| Sort then index | O(n log n) | Always sorts entire array |
| Quick Select | O(n) average | Only recurses one side |
| Median of Medians | O(n) worst case | Guaranteed linear, higher constant |

#### Space Complexity

| Case | Space | Explanation |
|------|-------|-------------|
| **Average** | **O(log n)** | Recursion depth |
| **Worst** | **O(n)** | Linear recursion on bad pivot |

**Key Properties:**
- ✅ In-place: No extra array needed
- ✅ Average O(n): Faster than sorting for single-element queries
- ❌ Modifies input array: Original order not preserved after partition
- ❌ Worst case O(n²): Use randomized pivot to mitigate

---

## 📚 Week 7 Summary

### Quick Sort Pivot Strategies Comparison

| Feature | Last Element | First Element | Median-of-Three |
|---------|-------------|---------------|-----------------|
| **Average Time** | O(n log n) | O(n log n) | O(n log n) |
| **Worst Case** | O(n²) on sorted | O(n²) on sorted | O(n²) on adversarial |
| **Extra work** | None | 1 swap | 3 comparisons + 1 swap |
| **Practical** | Simple | Simple | Best for real-world data |

### Quick Sort vs Quick Select

| Feature | Quick Sort | Quick Select |
|---------|-----------|--------------|
| **Goal** | Sort entire array | Find k-th smallest |
| **Recurse into** | Both sides | One side only |
| **Time (average)** | O(n log n) | O(n) |
| **Time (worst)** | O(n²) | O(n²) |
| **Space** | O(log n) | O(log n) |
| **Output** | Sorted array | Single element |

### Key Learnings

**1. Pivot Choice Matters:**
- Last/First pivot is simple but vulnerable to sorted inputs
- Median-of-three significantly reduces worst-case probability
- Randomized pivot (not implemented here) gives expected O(n log n) always

**2. Quick Select — One-Sided Recursion:**
- The only algorithmic difference from Quick Sort is recursing one side
- This single change reduces average time from O(n log n) to O(n)
- Useful when you only need the k-th element, not the full sorted order

**3. Both Modify the Array:**
- Partition rearranges elements in place
- After Quick Select, array is partially sorted up to the pivot
- If original order must be preserved, work on a copy

**4. Practical Use Cases:**
- Quick Select: finding median, top-k elements, percentiles
- Median-of-three pivot: default in many standard library sort implementations

---

## 🎯 Practice Questions

1. Trace Quick Sort step-by-step on `[5, 3, 8, 1, 9, 2]` using median-of-three pivot.
2. What input would cause worst-case O(n²) for median-of-three pivot?
3. Modify Quick Select to find the k-th **largest** element instead of smallest.
4. Why does Quick Select run in O(n) average but Quick Sort runs in O(n log n) average?
5. Implement Quick Select with a randomized pivot and analyse its expected time complexity.
6. Use Quick Select to find the **median** of an unsorted array in O(n) average time.

---

[← Back to Main](../README.md)