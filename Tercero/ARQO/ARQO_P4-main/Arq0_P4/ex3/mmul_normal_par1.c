#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "arqo3.h"
#include <omp.h>
/*
tipo ** generateMatrix(int);
tipo ** generateEmptyMatrix(int);
void freeMatrix(tipo **);
*/

/*     Private functions    */
int multiplyMatrix(tipo ** m1, tipo ** m2, tipo ** mf, int n);

/**
    * @brief Function to multiply two square matrixes of the same size
    * @param N: size of the matrixes
    * @return: the result of the multiplication
*/
int main(int argc, char ** argv)  {
    int N;  
    int num_threads;
    //int i=0;
    //int j=0;
    struct timeval fin,ini;
    if (argc != 3)  {
        fprintf(stderr,"Wrong amount of arguments. Please write argument for the size of matrix");
        return -1;
    }
    N = atoi(argv[1]);
    num_threads = atoi(argv[2]);
    omp_set_num_threads(num_threads);

    tipo ** m1 = generateMatrix(N);
    tipo ** m2 = generateMatrix(N);
    tipo ** mf = generateEmptyMatrix(N);
    if (m1 == NULL || m2 == NULL || mf == NULL)  {
        fprintf(stderr,"Error: could not allocate memory");
        return -1;
    }
    gettimeofday(&ini,NULL);
    multiplyMatrix(m1,m2,mf,N);
    gettimeofday(&fin,NULL);
    printf("Execution time: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
    /*printf("Resulting matrix: \n");
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
            printf("%lf  ", mf[i][j]);
		}
		printf("\n");
	}*/
    freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(mf);    
}

/**
    @brief: Funtion to multiply to matrixes of the same size.
    @param N: size of the matrixes
    @input: m1, m2: matrixes to multiply
    @input: mf: matrix to store the result
    @return: pointer to the matrix that contains the result of the multiplication

*/
int multiplyMatrix(tipo ** m1, tipo ** m2, tipo ** mf, int n)  {
    int i, j, k, aux;
    for (i = 0; i < n; i++)  {
        for (j = 0; j < n; j++)  {
            aux = 0;
            #pragma omp parallel for reduction(+:aux)
            for (k = 0; k < n; k++)  {
                aux += m1[i][k] * m2[k][j];
            }
            mf[i][j] = aux;
        }
    }
    return 0;
}

