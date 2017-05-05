// Standard includes
#include "mpi.h" 
#include <stdio.h> // printf
#include <stdbool.h> // boolean
#include <math.h> // ldexp

// PCG includes
#include "pcg_variants.h"
#include "entropy.h" 

int main(int argc,char *argv[]) { 
    int numtasks, rank; 
    bool nondeterministic_seed = true; // Flip this switch if you want
                                       // deterministic behaviour

    MPI_Status Stat; 
    MPI_Init(&argc,
             &argv); 
    MPI_Comm_size(MPI_COMM_WORLD,
                  &numtasks); 
    MPI_Comm_rank(MPI_COMM_WORLD,
                  &rank); 
    
    // Initialise RNG seed
    pcg32_random_t rng;
    if (nondeterministic_seed) {
        // Seed with external entropy
        uint64_t seeds[2];
        entropy_getbytes((void*)seeds,
                         sizeof(seeds));
        // XOR seed with rank to ensure unique seeds for each process
        pcg32_srandom_r(&rng,
                        seeds[0]^rank,
                        seeds[1]^rank);
    } else {
        // Seed with a fixed constant
        pcg32_srandom_r(&rng,
                        42u,
                        54u);
    }

    // Generate a floating point random number in the range [0,1)
    double random_double = ldexp(pcg32_random_r(&rng),
                                 -32);

    // Print random number
    printf("%f\n", random_double);

    MPI_Finalize(); 
    
    return 0;
} 