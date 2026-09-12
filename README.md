<<<<<<< HEAD
# algorithms-c

Three classic algorithms implemented from scratch in C: a sorting suite, a
lexicon-based sentiment analyzer, and a particle swarm optimizer. Written for
MECHTRON 2MP3 (Programming for Mechatronics) at McMaster University, Fall 2024.

| Project | What it does |
|---|---|
| [`sorting-algorithms/`](./sorting-algorithms) | Bubble, Insertion, Merge, Heap, and Counting sort in C, compiled into a shared library and benchmarked from Python against `sorted()` and `numpy.sort()`. |
| [`sentiment-analysis-vader/`](./sentiment-analysis-vader) | VADER sentiment analysis re-implemented from scratch in C — lexicon parsing, negation/intensifier handling, and compound scoring. |
| [`particle-swarm-optimization/`](./particle-swarm-optimization) | A particle swarm optimizer in C, tested against eight standard optimization benchmark functions. |

Each project folder has its own README with a full write-up: objective, design,
results, and how to build and run it.

## Building

Each project builds independently with `make` (gcc, C99, no external dependencies
beyond the C standard library and `libm`). See each project's README for exact
commands.

## A note on scope

This repo covers three of the four assignments from the course — the fourth
(a custom `sqrt()` implementation and analysis) isn't included, as its source files
weren't recovered from the original coursework archive. Course-provided starter files
and instructor assignment handouts are also excluded; each project README summarizes
the assignment brief in its own words instead.

---
*Madeline LeBreton — [github.com/madelinelebreton](https://github.com/madelinelebreton)*
=======
# c-sorting-algorithms
Implementation and benchmarking of classic sorting algorithms in C, with a shared C library accessed from Python.
>>>>>>> 232e6fa89b582051479a438cf8d1e47ff655f3d1
