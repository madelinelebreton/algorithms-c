// utility.h
// written by Madeline with help from ChatGPT
// this file declares all needed structures and functions used in PSO.c


#ifndef UTILITY_H
#define UTILITY_H

#define STOPPING_PRECISION 10e-10
#define THRESHOLD_COUNTER 200
#define DIVERSIFY_FRAC .1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Function pointer type for objective functions
typedef double (*ObjectiveFunction)(int, double *);

typedef struct Bound{
    double lowerBound;
    double upperBound;
}Bound;


// Function prototypes
double random_double(double min, double max);
double pso(ObjectiveFunction objective_function, int NUM_VARIABLES, Bound *bounds, int NUM_PARTICLES, int MAX_ITERATIONS, double best_position[]);

// CODE: declare other functions and structures if necessary

double **allocate_2d_array(int rows, int cols); // 
void free_2d_array(double **array, int rows); //

#endif // UTILITY_H



