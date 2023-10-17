#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int sig;
    pid_t pid;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s -<signal> <pid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sig = atoi(argv[1] + 1);
    pid = (pid_t)atoi(argv[2]);

    /* Rellenar Código */
	kill(pid,sig);	
//	execlp("kill",argv[1],pid);
	

    exit(EXIT_SUCCESS);
}
