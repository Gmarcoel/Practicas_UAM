#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "arqo3.h"
/*
    Once the program that performs matrix multiplication has been developed, you have to create a new 
    program from the previous one that performs “transposed multiplication”. Note that in this case the 
    result must be equivalent to the previous program, but the storage of matrix B changes. The elements 
    of the transposed multiplication are calculated according to the following expression:
*/

/* Private functions */
int trasposedMultiplication(tipo ** m1, tipo ** m2, tipo ** mt, tipo ** mf, int N);

/*
    Function that performs transposed multiplication
    @param N: size of the matrixes
*/
int main(int argc, char ** argv)  {
    int N;
    //int i=0;
    //int j=0;
    struct timeval fin,ini;
    if (argc != 2)  {
        fprintf(stderr,"Wrong amount of arguments. Please write argument for the size of matrix");
        return -1;
    }
    N = atoi(argv[1]);
    tipo ** m1 = generateMatrix(N);
    tipo ** m2 = generateMatrix(N);
    tipo ** mt = generateEmptyMatrix(N);
    tipo ** mf = generateEmptyMatrix(N);
    if (m1 == NULL || m2 == NULL || mf == NULL)  {
        fprintf(stderr,"Error: could not allocate memory");
        return -1;
    }

    gettimeofday(&ini,NULL);
    trasposedMultiplication(m1,m2,mt,mf,N);
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

/*
    Funtion to multiply two matrixes where one is transposed
    @param m1: first matrix
    @param m2: second matrix
    @param mf: matrix to store the result
    @param N: size of the matrixes
    @return 0 if everything went ok, -1 otherwise
*/
int trasposedMultiplication(tipo ** m1, tipo ** m2, tipo ** mt, tipo ** mf, int N)  {
    int i,j,k;
    for (i = 0; i < N; i++)  {
        for (j = 0; j < N; j++)  {
            mt[i][j] = m2[j][i];
        }
    }


    for (i = 0; i < N; i++)  {
        for (j = 0; j < N; j++)  {
            for (k = 0; k < N; k++)  {
                mf[i][j] += m1[i][k] * mt[j][k];
            }
        }
    }
    return 0;
}