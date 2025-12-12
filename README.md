# DAA-ch.sc.u4cse24234

**Course:** Design and Analysis of Algorithms (DAA)  
**Repository:** Laboratory Programs Collection  
**Student ID:** ch.sc.u4cse24234  
**Name:** Parupudi Sridatta Bharadwaj

---

## 📚 Lab Sessions

<details open>
<summary>📁 <b>Week 1 - Basic Algorithms & Complexity Analysis</b></summary>

### Topics Covered
- Time and space complexity fundamentals
- Mathematical formulas
- Recursion
- Array operations

### Programs
1. [Sum of first n natural numbers](./Week-1/README.md#program-1-sum-of-first-n-natural-numbers)
2. [Sum of squares of first n natural numbers](./Week-1/README.md#program-2-sum-of-squares)
3. [Sum of cubes of first n natural numbers](./Week-1/README.md#program-3-sum-of-cubes)
4. [Factorial using recursion](./Week-1/README.md#program-4-factorial-using-recursion)
5. [Transpose of 3x3 matrix](./Week-1/README.md#program-5-matrix-transpose)
6. [Fibonacci series (first n terms)](./Week-1/README.md#program-6-fibonacci-series)

[📄 **View Full Week 1 Documentation & Analysis →**](./Week-1/README.md)

</details>

<details open>
<summary>📁 <b>Week 2 - Sorting Algorithms</b></summary>

### Topics Covered
- Comparison-based sorting
- Divide and conquer approach
- Heap data structure
- Distribution-based sorting

### Programs
1. [Bubble Sort](./Week-2/README.md#program-1-bubble-sort)
2. [Selection Sort](./Week-2/README.md#program-2-selection-sort)
3. [Insertion Sort](./Week-2/README.md#program-3-insertion-sort)
4. [Heap Sort](./Week-2/README.md#program-4-heap-sort)
5. [Bucket Sort](./Week-2/README.md#program-5-bucket-sort)

[📄 **View Full Week 2 Documentation & Analysis →**](./Week-2/README.md)

</details>

<details>
<summary>📁 <b>Week 3 - Coming Soon</b></summary>

### Topics
- To be updated

</details>

---

## 📂 Repository Structure

```
DAA-ch.sc.u4cse24234/
├── README.md              # This file
├── .gitignore            # Git ignore configuration
├── Week-1/               
│   ├── README.md         # Week 1 detailed documentation
│   ├── questions.txt     # Problem statements
│   ├── question1.c       # Sum of n natural numbers
│   ├── question2.c       # Sum of squares
│   ├── question3.c       # Sum of cubes
│   ├── question4.c       # Factorial (recursive)
│   ├── question5.c       # Matrix transpose
│   ├── question6.c       # Fibonacci series
│   └── outputs/          # Program output screenshots
└── Week-2/               
    ├── README.md         # Week 2 detailed documentation
    ├── bubble_sort.c     # Bubble sort implementation
    ├── selection_sort.c  # Selection sort implementation
    ├── insertion_sort.c  # Insertion sort implementation
    ├── heap_sort.c       # Heap sort implementation
    ├── bucket_sort.c     # Bucket sort implementation
    └── outputs/          # Program output screenshots
```

---

## 🚀 How to Use This Repository

### Browsing Documentation
- Click on any week above to view detailed complexity analysis
- Each program includes time/space complexity breakdown
- Code explanations and output examples provided

### Running Programs

#### Week 1 Programs
```bash
# Navigate to Week-1
cd Week-1

# Compile any program (example: question1.c)
gcc question1.c -o question1

# Run the executable
./question1

# Or on Windows
question1.exe
```

#### Week 2 Programs
```bash
# Navigate to Week-2
cd Week-2

# Compile any sorting program
gcc bubble_sort.c -o bubble_sort
gcc selection_sort.c -o selection_sort
gcc insertion_sort.c -o insertion_sort
gcc heap_sort.c -o heap_sort
gcc bucket_sort.c -o bucket_sort

# Run
./bubble_sort
```

### Compile All Programs at Once
```bash
# Week 1
cd Week-1
gcc question1.c -o q1
gcc question2.c -o q2
gcc question3.c -o q3
gcc question4.c -o q4
gcc question5.c -o q5
gcc question6.c -o q6

# Week 2
cd ../Week-2
gcc bubble_sort.c -o bubble
gcc selection_sort.c -o selection
gcc insertion_sort.c -o insertion
gcc heap_sort.c -o heap
gcc bucket_sort.c -o bucket
```

---

## 📊 Quick Complexity Reference

### Week 1 - Basic Algorithms

| Program | Time | Space | Type |
|---------|------|-------|------|
| Sum of n numbers | O(1) | O(1) | Formula-based |
| Sum of squares | O(1) | O(1) | Formula-based |
| Sum of cubes | O(1) | O(1) | Formula-based |
| Factorial (recursive) | O(n) | O(n) | Recursion |
| Matrix transpose | O(n²) | O(n²) | Iteration |
| Fibonacci series | O(n) | O(1) | Iteration |

### Week 2 - Sorting Algorithms

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | ✅ Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | ❌ No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | ✅ Yes |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(log n) | ❌ No |
| Bucket Sort | O(n+k) | O(n+k) | O(n²) | O(n+k) | ✅ Yes* |

*Depends on internal sorting algorithm

---

## 🎯 Learning Outcomes

### Week 1
- Understanding time and space complexity analysis
- Big-O notation and complexity classes
- Recursion vs iteration trade-offs
- Formula-based optimization techniques

### Week 2
- Comparison-based vs distribution-based sorting
- Stable vs unstable sorting algorithms
- In-place vs out-of-place sorting
- Algorithm selection based on input characteristics

---

## 📖 Quick Links

- [Week 1 Full Documentation](./Week-1/README.md)
- [Week 2 Full Documentation](./Week-2/README.md)

---

**Last Updated:** December 2024
