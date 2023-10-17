#include <stdlib.h>
#include <stdio.h>
#include <x86intrin.h>
#include <sys/time.h>

#define ARRAY_SIZE 2048
//#define NUMBER_OF_TRIALS 1 // 1000000
int NUMBER_OF_TRIALS = 1;

/*
 * Statically allocate our arrays.  Compilers can
 * align them correctly.
 */
static double a[ARRAY_SIZE], b[ARRAY_SIZE], c;

/* Intrinsics */
__m256d mm = {1.0001, 1.0001, 1.0001, 1.0001};
__m256d sum = {0.0, 0.0, 0.0, 0.0}; // to hold partial sums

int main(int argc, char *argv[])
{
    int i, t;
    double m = 1.0001;
    struct timeval time1, time2;

    // if one argument is given, use it as the number of trials
    if (argc > 1) {
        NUMBER_OF_TRIALS = atoi(argv[1]);
    }

    // Times
    gettimeofday(&time1, NULL);

    /* Populate A and B arrays using intrinsics */
    for (i = 0; i < ARRAY_SIZE; i += 4)
    {
        // Initialize b vector as __m256d b = {0, 1, 2, 3}.
        __m256d bi = _mm256_set_pd(0, 1, 2, 3);
        // Similar idea for a.
        __m256d ai = _mm256_set_pd(1, 2, 3, 4);
        // Add the i constant to each element of a and b.
        ai = _mm256_add_pd(ai, _mm256_set_pd(i,i,i,i));
        bi = _mm256_add_pd(bi, _mm256_set_pd(i,i,i,i));
        // Store the result in the array.
        _mm256_store_pd(&a[i], ai);
        _mm256_store_pd(&b[i], bi);

    }


    /* Perform an operation a number of times */
    for (t = 0; t < NUMBER_OF_TRIALS; t++)
    {
        c = 0;
        sum[0] = 0;
        sum[1] = 0;
        sum[2] = 0;
        sum[3] = 0;
        for (i = 0; i < ARRAY_SIZE; i = i + 4)
        {
            // Load arrays
            __m256d va = _mm256_load_pd(&a[i]);
            __m256d vb = _mm256_load_pd(&b[i]);
            // Compute m*a+b
            __m256d tmp = _mm256_fmadd_pd(mm, va, vb);
            // Accumulate results
            sum = _mm256_add_pd(tmp, sum);
        }
        c = 0;
        for (int i = 0; i < 4; i++)
        {
            c += sum[i];
        }

        
    }
    gettimeofday(&time2, NULL);
    printf("%lf ", c);
    printf("%li", time2.tv_sec - time1.tv_sec);

    return time2.tv_usec - time1.tv_usec;
}
