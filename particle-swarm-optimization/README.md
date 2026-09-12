# Particle Swarm Optimization in C

A C implementation of Particle Swarm Optimization (PSO).
Population-based framework to minimize an objective function by simulating a
swarm of particles moving through the search space, each pulled toward its own best
known position and the swarm's global best.

Tested against eight standard optimization benchmark functions: Griewank, Levy,
Rastrigin, Rosenbrock, Schwefel, Dixon-Price, Michalewicz, and Styblinski-Tang;
chosen for their varied, deliberately difficult landscapes (many local minima, flat
regions, steep curving valleys) that stress different aspects of an optimizer.

## What's here
- **`PSO.c` / `utility.h`**: the PSO algorithm itself: particle position/velocity
  updates, personal- and global-best tracking, a stagnation-triggered
  re-diversification step to help escape local minima, and an early-stopping
  precision threshold.
- **`OF.c` / `OF_lib.h`**: the eight benchmark objective functions (not written by me).
- **`main.c`**: a command line driver parsing the objective function name and PSO
  parameters from `argv`, runs the optimizer, and prints the result.
- **`Makefile`**: builds the `pso` executable.

## How it works

Each particle *i* has a position **xᵢ**, velocity **vᵢ**, and personal best position
**pᵢ**. At each iteration, velocity updates blend three influences: inertia (the
particle's previous motion), a cognitive term (pull toward its own best position),
and a social term (pull toward the swarm's global best):

```
v[i][j](t+1) = w·v[i][j](t) + c1·r1·(p[i][j] − x[i][j](t)) + c2·r2·(g[j] − x[i][j](t))
```

If the swarm stagnates (no improvement for a set number of iterations), a fraction of
particles are re-randomized to inject diversity and escape local minima. The search
stops early once the global best fitness is within a small tolerance of convergence.

## Results
Optimal fitness and CPU time across the eight benchmark functions at 10 decision
variables:

| Function         | Bounds        | Particles | Iterations | Optimal fitness | CPU time (s) |
|------------------|:-------------:|----------:|-----------:|-----------------:|-------------:|
| Griewank         | [-600, 600]   | 50        | 45,456     | 0.0000            | 0.834        |
| Levy             | [-10, 10]     | 50,000    | 136        | 0.0000            | 2.176        |
| Rastrigin        | [-5.12, 5.12] | 5,000     | 277        | 0.0000            | 0.661        |
| Rosenbrock       | [-5, 10]      | 5,000     | 10,736     | 0.0000            | 59.126       |
| Schwefel         | [-500, 500]   | 50,000    | 988        | 0.0000            | 17.721       |
| Dixon-Price      | [-10, 10]     | 50,000    | 14,023     | 0.0000            | 141.429      |
| Michalewicz      | [0, π]        | 50,000    | 500        | -9.6602           | 20.041       |
| Styblinski-Tang  | [-5, 5]       | 50,000    | 892        | -391.6617         | 21.324       |

Performance scaled predictably with dimensionality: at 50 and 100 decision variables,
CPU time grew substantially, and the harder landscapes (Schwefel, Dixon-Price,
Michalewicz) needed more iterations to converge. The diversification mechanism let
the swarm keep finding new minima rather than getting stuck, especially at lower
dimensions.

## Running it

```bash
make
./pso <objective_function_name> <num_variables> <lower_bound> <upper_bound> <num_particles> <max_iterations>

# example
./pso griewank 10 -50 50 500 1000
```

