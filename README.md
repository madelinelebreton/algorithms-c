# algorithms-c
Three classic algorithms implemented from scratch in C: a sorting suite, a lexicon-based sentiment analyzer, and a particle swarm optimizer. 

| Project | What it does |
|---|---|
| [`sorting-algorithms/`](./sorting-algorithms) | Bubble, Insertion, Merge, Heap, and Counting sort in C, compiled into a shared library and benchmarked from Python against `sorted()` and `numpy.sort()`. |
| [`sentiment-analysis-vader/`](./sentiment-analysis-vader) | VADER sentiment analysis re-implemented from scratch in C — lexicon parsing, negation/intensifier handling, and compound scoring. |
| [`particle-swarm-optimization/`](./particle-swarm-optimization) | A particle swarm optimizer in C, tested against eight standard optimization benchmark functions. |

## Building

Each project builds independently with `make` (gcc, C99, no external dependencies
beyond the C standard library and `libm`). See each project's README for exact
commands.
