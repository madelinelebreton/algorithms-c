// PSO.c
// written by Madeline with help from ChatGPT
// this file implements the particle swarm optimization logic and necessary functions

#include "utility.h"

// this function dynamically allocates memory for a 2D array
double **allocate_2d_array(int rows, int cols) {
    double **array = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        array[i] = (double *)malloc(cols * sizeof(double));
    }
    return array;
}

// this function frees allocated memory from a 2D array
void free_2d_array(double **array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

// this function generates a random double between bounds
double random_double(double min, double max) {
    return min + (rand() / (double)RAND_MAX) * (max - min);
}

// this function uses the particle swarm optimization algorithm to minimize objective functions
double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double *best_position) {
    double w = 0.7, c1 = 1.5, c2 = 1.5; // PSO constants

    // allocate memory for particles
    double **x = allocate_2d_array(NUM_PARTICLES, NUM_VARIABLES); // each particle i has POSITION: xi=[xi1, .., xid], where d is # decision vars. xi is the input array to objective function
    double **v = allocate_2d_array(NUM_PARTICLES, NUM_VARIABLES); // each particle i has VELOCITY: vi=[vi1, .., vid]. xij in xi has velocity vij. vi shows how xi should move to minimize OF
    double **p = allocate_2d_array(NUM_PARTICLES, NUM_VARIABLES); // each particle i has PERSONAL BEST POSITIONS: pi=[pi1, .., pid] stores position xi that has produced the lowest OF
    double *fpbest = (double *)malloc(NUM_PARTICLES * sizeof(double)); // FITNESS VALUES: f(xi), evaluates OF for set of decision variables xi
    double fgbest = INFINITY; // global best fitness
    double *g = (double *)malloc(NUM_VARIABLES * sizeof(double)); // GLOBAL BEST POSITION: g=[g1, .., gd] determined by best fitness among all particles. results in lowest OF for given pis

    // initialize particles, iterating through each dimension of all particles
    for (int i = 0; i < NUM_PARTICLES; i++) {
        for (int j = 0; j < NUM_VARIABLES; j++) {
            x[i][j] = random_double(bounds[j].lowerBound, bounds[j].upperBound);
            v[i][j] = random_double(bounds[j].lowerBound * 0.8, bounds[j].upperBound * 0.8);
            p[i][j] = x[i][j];
        }
        fpbest[i] = objective_function(NUM_VARIABLES, x[i]);

        if (fpbest[i] < fgbest) {
            fgbest = fpbest[i];
            for (int j = 0; j < NUM_VARIABLES; j++) {
                g[j] = p[i][j];
            }
        }
    }

    // PSO iterative optimization
    int stagnant_counter = 0;
    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        int improvement_flag = 0; // track if improvement happened

        for (int i = 0; i < NUM_PARTICLES; i++) {
            for (int j = 0; j < NUM_VARIABLES; j++) {
                double r1 = random_double(0.0, 1.0);
                double r2 = random_double(0.0, 1.0);

                // update velocities
                v[i][j] = w * v[i][j] + c1 * r1 * (p[i][j] - x[i][j]) + c2 * r2 * (g[j] - x[i][j]);
                x[i][j] += v[i][j];

                // ensure positions remain within bounds
                if (x[i][j] < bounds[j].lowerBound) x[i][j] = bounds[j].lowerBound;
                if (x[i][j] > bounds[j].upperBound) x[i][j] = bounds[j].upperBound;
            }

            // recompute fitness
            double fitness = objective_function(NUM_VARIABLES, x[i]);
            if (fitness < fpbest[i]) {
                fpbest[i] = fitness;
                for (int j = 0; j < NUM_VARIABLES; j++) {
                    p[i][j] = x[i][j];
                }
            }

            // update global best
            if (fitness < fgbest) {
                fgbest = fitness;
                for (int j = 0; j < NUM_VARIABLES; j++) {
                    g[j] = x[i][j];
                }
                improvement_flag = 1; // improvement detected
            }
        }

        // check for stagnation
        if (!improvement_flag) {
            stagnant_counter++;
        } else {
            stagnant_counter = 0; // reset if improvement occurred
        }

        // diversify if stagnation persists
        if (stagnant_counter >= THRESHOLD_COUNTER) {
            for (int i = 0; i < NUM_PARTICLES; i++) {
                if (random_double(0.0, 1.0) < DIVERSIFY_FRAC) { // reinitialize a fraction of particles
                    for (int j = 0; j < NUM_VARIABLES; j++) {
                        x[i][j] *= random_double(bounds[j].lowerBound, bounds[j].upperBound);
                        v[i][j] *= random_double(bounds[j].lowerBound * 0.8, bounds[j].upperBound * 0.8);
                    }
                    fpbest[i] = objective_function(NUM_VARIABLES, x[i]);
                    if (fpbest[i] < fgbest) {
                        fgbest = fpbest[i];
                        for (int j = 0; j < NUM_VARIABLES; j++) {
                            g[j] = x[i][j];
                        }
                    }
                }
            }
            stagnant_counter = 0; // reset stagnation counter after injecting diversity
        }

        // check for stopping precision
        if (fabs(fgbest) < STOPPING_PRECISION) {
            printf("Stopping early at iteration %d\n", iter);
            break;
        }
    }

    // store the global best position
    for (int j = 0; j < NUM_VARIABLES; j++) {
        best_position[j] = g[j];
    }

    // free dynamically allocated memory
    free_2d_array(x, NUM_PARTICLES);
    free_2d_array(v, NUM_PARTICLES);
    free_2d_array(p, NUM_PARTICLES);
    free(fpbest);
    free(g);

    return fgbest;
}
