#include <stdio.h>
#include <errno.h>

int main(int argc, char** argv){
	int e;
	    if (argc!=2){
			    printf("Número de argumentos incorrecto");
				return -1;
		}
		    fopen(argv[1],"r");
			e = errno;
		    printf("%i\n",e);
			errno = e;
			perror("fopen");
}

