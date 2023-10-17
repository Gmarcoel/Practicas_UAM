// ----------- Arqo P4-----------------------
// pescalar_par2
// ¿Funciona correctamente?
//
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "arqo4.h"

int main(int argc, char *argv[])
{
	int nproc;
	float *A=NULL, *B=NULL;
	long long k=0;
	struct timeval fin,ini;
	double mult=0;
	double sum=0;
	int n;

    if (argc == 2) {
        n = atoi(argv[1]);
    }
    else {
		printf("Need argument <size>\n");
    }

       
	A = generateVectorOne(n);
	B = generateVectorOne(n);
	if ( !A || !B )
	{
		printf("Error when allocationg matrix\n");
		freeVector(A);
		freeVector(B);
		return -1;
	}
	
        nproc=omp_get_num_procs();
        omp_set_num_threads(nproc);   
     
        printf("Se han lanzado %d hilos.\n",nproc);

	gettimeofday(&ini,NULL);
	/* Bloque de computo */
	sum = 0;

        #pragma omp parallel for reduction(+:sum) private(mult)
	for(k=0;k<n;k++)
	{
		mult=A[k]*B[k];
		sum += mult;
	}
	/* Fin del computo */
	gettimeofday(&fin,NULL);

	printf("Resultado: %f\n",sum);
	printf("Tiempo: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
	freeVector(A);
	freeVector(B);

	return 0;
}
