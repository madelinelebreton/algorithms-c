# Sorting Algorithms in C — with a Python Case Study

5 classic sorting algorithms implemented from scratch in C, compiled into a shared
library (`libmysort.so`), and benchmarked from Python for time and space complexity.
Learned as an exercise for programming in C.

## What's here
- **`mySort.c` / `mySort.h`**: Bubble, Insertion, Merge, Heap, and Counting sort,
  implemented from scratch in C.
- **`main.c`**: a small C test harness that runs each algorithm against a sample array.
- **`Makefile`**: builds `libmysort.so`, a shared library exposing the sort functions
  so they can be called directly from Python via `ctypes`.
- **`mySort_test.ipynb`**: loads `libmysort.so`, times each algorithm against
  Python's built-in `sorted()` and `numpy.sort()`, and plots the results.

## Results
Empirical CPU time to sort the same large array, compared against each algorithm's
theoretical time/space complexity:

| Sort Method       | Time complexity | Space complexity | CPU time (s) |
|--------------------|:---------------:|:-----------------:|-------------:|
| Bubble             | O(n²)           | O(1)               | 645.14       |
| Insertion          | O(n²)           | O(1)               | 104.35       |
| Merge              | O(n log n)      | O(n)               | 0.089        |
| Heap               | O(n log n)      | O(n)               | 0.088        |
| Counting           | O(n + range)    | O(range)           | 0.015        |
| Python `sorted()`  | O(n log n)      | O(n)               | 0.323        |
| `numpy.sort()`     | O(n log n)      | O(n)               | 0.044        |

Bubble and Insertion sort's O(n²) behaviour makes them impractical at scale. Merge and
Heap sort perform comparably to each other, as expected from their shared O(n log n)
complexity. Counting sort is fastest here because the test data is a narrow range of
integers, which is exactly the case it's suited for — but its performance depends on
that range, not just `n`, so it doesn't generalize to arbitrary data the way the
comparison-based sorts do.

## Running it
```bash
make                                   # builds libmysort.so
gcc -o testSort main.c -L. -lmysort    # compiles and links the C test harness
./testSort
```

To reproduce the benchmark, open `mySort_test.ipynb` in the same directory (it loads
`libmysort.so` via `ctypes`).
